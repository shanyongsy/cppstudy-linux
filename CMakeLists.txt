# 设置 cmake 的最低版本
cmake_minimum_required(VERSION 3.12)

# 输出路径
message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

# 设置工程名和版本
project(hello VERSION 1.51.60.2 DESCRIPTION "This is my study cpp project" HOMEPAGE_URL "baidu.com")

# project(studycpp DESCRIPTION "This is my study cpp project" HOMEPAGE_URL "baidu.com")

# 指定为C++17 版本
set(CMAKE_CXX_STANDARD 17)

# true - 强制要求使用 c++ 标准版本，如果不支持，则报错，而不是降低版本
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加调试信息
set(CMAKE_BUILD_TYPE Debug)

# 添加编译选项（使用 gprof）
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")

# 三方库 include
# include_directories(third/openssl/include)
include_directories(third)
include_directories(third/boost/include)

# 三方库 lib
# link_directories(third/openssl/lib)
link_directories(third/boost/lib)

# 本地库 include
include_directories(include)
include_directories(include/md5)
include_directories(include/encrypt)
include_directories(include/boost)
include_directories(include/system)

# 本地库 lib
add_library(my_common ./common/func.cpp ./common/http_server.cpp)
add_library(my_md5 ./common/md5/md5.cpp ./common/md5/md5c.c)
add_library(my_encrypt ./common/md5/md5.cpp ./common/encrypt/encrypt.cpp)
add_library(my_boost ./common/boost/boost.cpp)
add_library(my_system ./common/system/system.cpp)

# add_library(https ./common/https/httpsserver.cpp)
add_executable(hello ./main.cpp)

# 目标文件
# target_link_libraries(hello common md5 encrypt pthread -lssl -lcrypto)
target_link_libraries(hello my_common my_md5 my_encrypt my_boost my_system -lpthread)

# link_directories()

# find_library(VALGRIND_LIBRARIES valgrind)
# if(VALGRIND_LIBRARIES)
# target_link_libraries(hello ${VALGRIND_LIBRARIES})
# else()
# message("${VALGRIND_LIBRARIES}")
# endif()

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

# # [gprof]添加 -pg 选项以启用 gprof 收集功能
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")

# # [gprof]编写自定义构建命令
# add_custom_target(gprof
# COMMAND ${CMAKE_COMMAND} -E remove libhello.a hello
# COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${PROJECT_SOURCE_DIR}/src
# COMMAND ${MAKE}
# COMMAND ${PROJECT_BINARY_DIR}/hello
# COMMAND ${CMAKE_COMMAND} -E remove gmon.out
# COMMAND ${CMAKE_COMMAND} -E env CPUPROFILE=gmon.out ./${PROJECT_BINARY_DIR}/hello
# COMMAND ${CMAKE_STRIP} --strip-debug ${PROJECT_BINARY_DIR}/hello
# COMMAND ${CMAKE_COMMAND} -E env GPROF_PATH=/usr/bin/gprof ${GPROF_PATH} ${PROJECT_BINARY_DIR}/hello gmon.out > ${PROJECT_BINARY_DIR}/gprof.out
# WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
# COMMENT "Running gprof"
# )

# # [gprof]将 gprof 命令添加到构建目标中
# add_dependencies(gprof hello)
