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

// split string
void split_string();

// test_mac_to_hex_string
void test_mac_to_hex_string();

// test_reportmsg
void test_reportmsg();

//
void id_level_value();

std::string g_GetLocalTimeString(const time_t& t);

void fsb_MapToPoint(int x, int y);
