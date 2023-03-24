# 设置 cmake 的最低版本
cmake_minimum_required(VERSION 3.12)

# 输出路径
message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

# 设置工程名和版本
project(hello VERSION 1.51.60.2 DESCRIPTION "This is my study cpp project" HOMEPAGE_URL "baidu.com")
#project(studycpp DESCRIPTION "This is my study cpp project" HOMEPAGE_URL "baidu.com")

# 指定 c++ 标准版本
# 指定为C++11 版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug) # 添加调试信息

include_directories(include)

add_library(common ./common/checkptr.cpp)
add_executable(hello ./main.cpp)
target_link_libraries(hello common -lpthread)

# 从文件中读取版本信息,将内容读入 PROGRAM_VERSION 变量中，该变量会去掉尾部的空格。当设置了变量 PROGRAM_VERSION ，就可以使用它来配置 version.hpp.in ，生成 generated/version.hpp 
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION")
  file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" PROGRAM_VERSION)
  string(STRIP "${PROGRAM_VERSION}" PROGRAM_VERSION)
else()
  message(FATAL_ERROR "File ${CMAKE_CURRENT_SOURCE_DIR}/VERSION not found")
endif()
# 基于 version.h.in 生成 version.h
configure_file(
  version.h.in
  generated/version.h
  @ONLY
)
# needs to find the generated header file
target_include_directories(hello
PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}/generated
)
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")
message("PROJECT_VERSION_MAJOR = ${PROJECT_VERSION_MAJOR}")
message("PROJECT_VERSION_MINOR = ${PROJECT_VERSION_MINOR}")
message("PROJECT_VERSION_PATCH = ${PROJECT_VERSION_PATCH}")
message("PROJECT_VERSION_TWEAK = ${PROJECT_VERSION_TWEAK}")
message("PROJECT_VERSION = ${PROJECT_VERSION}")


