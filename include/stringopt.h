#pragma once
#include <sstream>
#include <string>

// key=value[tail]
template <typename T>
inline std::string key_value_to_string(const char* key, const T& value, const char* tail = ",")
{
    std::ostringstream  buf;
    buf << key << "=" << std::to_string(value) << tail;
    return buf.str();
}

// key=value[tail]
inline std::string key_value_to_string(const char* key, const char* value, const char* tail = ",")
{
    std::ostringstream  buf;
    buf << key << "=" << value << tail;
    return buf.str();
}

#include <sstream>
#include <string>
//#include <stdexcept>

template <typename T>
void appendKeyValue(std::ostringstream& os, const std::string& key, const T& value) {
    os << key << "=" << value << ",";
}

void appendKeyValue(std::ostringstream& os, const std::string& key, const std::string& value) {
    os << key << "=" << value << ",";
}

template <typename T>
void appendKeyValue(std::ostringstream& os, const std::string& key, const T* value) {
    appendKeyValue(os, key, std::string(value));
}

void appendKeyValue(std::ostringstream& os, const std::string& key, const char* value) {
    appendKeyValue(os, key, std::string(value));
}

template <typename T, typename... Args>
void appendKeyValue(std::ostringstream& os, const std::string& key, const T& value, Args... args) {
    appendKeyValue(os, key, value);
    appendKeyValue(os, args...);
}

template <typename... Args>
std::string generateKeyValueString(Args... args) {
    // if (sizeof...(args) % 2 != 0) {
    //     throw std::invalid_argument("The number of arguments must be even.");
    // }
    std::ostringstream os;
    appendKeyValue(os, args...);
    std::string result = os.str();
    result.pop_back(); // 去掉最后一个逗号
    return result;
}

