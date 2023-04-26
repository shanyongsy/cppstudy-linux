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
