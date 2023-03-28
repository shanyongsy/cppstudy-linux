#pragma once

#include <memory>
#include "struct_def.h"

// example : weakptr
void example_weakptr(std::weak_ptr<PlayerInfo> p);

// example : temp
void example_tf();

// example : example_signal_handler_register
void example_signal_handler_register();

// make md5 example
void calculate_md5_example();

// make md5 for string
void calculate_string_md5(const std::string &in, std::string &out);

// make md5 for file
bool calculate_file_md5(const std::string &file, std::string &out);
