#include <iostream>
#include <arpa/inet.h>
#include <memory>
#include <string>
#include "string.h"
#include <list>
#include <unistd.h> //sleep
#include <thread>
#include <pthread.h>

#include "memory"

#include "version.h"
#include "func.h"
#include "struct_def.h"
#include "http_server.h"
#include "encrypt.h"
#include "boost.h"
#include "system.h"

typedef unsigned long DWORD;

int main(int argc, char *argv[])
{
	// example : signal
	example_signal_handler_register();

	// example : system
	example_system();

	// example : boost
	// example_boost_tokenizer();
	// example_boost_format();
	// example_std_splite();
	// example_boost_splite();

	// // example : encrypt
	// test_encrypt();

	// // example : split
	// split_string();

	// // example : start http server
	// std::thread t_http_server(http_server_run, 9000);
	// t_http_server.detach();

	// // example : version
	// if (argc >= 2)
	// {
	// 	std::string option = argv[1];
	// 	if (option == "--version")
	// 	{
	// 		// std::cout <<  PROJECT_VERSION << std::endl;
	// 		std::cout << PROGRAM_VERSION << std::endl;
	// 	}
	// }

	// // example : md5
	// calculate_md5_example();

	// // example : string md5
	// if (argc >= 3)
	// {
	// 	std::string option = argv[1];
	// 	if (option == "--md5s")
	// 	{
	// 		std::string value = argv[2];
	// 		std::string out;
	// 		calculate_string_md5(value, out);

	// 		std::cout << value << ":\n"
	// 				  << out << std::endl
	// 				  << std::endl;
	// 		char md5_1[64] = {};
	// 		strncpy(md5_1, out.c_str(), out.size());
	// 		std::cout << "strncpy:\n"
	// 				  << md5_1 << std::endl
	// 				  << std::endl;
	// 		char md5_2[64] = {};
	// 		out.copy(md5_2, out.size());
	// 		std::cout << "std::string.copy:\n"
	// 				  << md5_2 << std::endl
	// 				  << std::endl;

	// 		std::cout << "std::string.capacity:\n"
	// 				  << out.capacity() << std::endl;
	// 		std::cout << "std::string.size:\n"
	// 				  << out.size() << std::endl;
	// 		std::cout << "std::string.length:\n"
	// 				  << out.length() << std::endl;
	// 	}
	// }

	// // example : file md5
	// if (argc >= 3)
	// {
	// 	std::string option = argv[1];
	// 	if (option == "--md5f")
	// 	{
	// 		std::string value = argv[2];
	// 		std::string out;
	// 		calculate_file_md5(value, out);
	// 		std::cout << out;
	// 	}
	// }

	// // example : auto ptr
	// std::shared_ptr<PlayerInfo> sp(new PlayerInfo("小明", 1000));
	// // sp.reset();
	// example_weakptr(sp);
	// // sleep(300);

	// // example : argc argv
	// std::cout << argc << std::endl;
	// for(int i = 0; i < argc; i++)
	// {
	// 	std::cout << argv[i] << std::endl;
	// }

	// // example : thread
	// // ps: g++ helloworld.cpp -lpthread
	// std::thread t(example_tf);
	// t.join();
	// sleep(300);

	// example : strncpy 测试
	char c1[] = "123";
	std::string strlog = "";
	strlog.append(c1, 5);
	std::cout << strlog << std::endl;
	// char c2[6] = {};
	// strncpy(c2, c1, 6);
	// c2[5] = '\0';
	// std::string strInfo2 = c2;
	// std::cout << "strInfo2 = " << strInfo2 << std::endl;
	// std::string strInfo1 = c1;
	// std::cout << "strInfo1 = " << strInfo1 << std::endl;

	// // example : make a dump
	// int* p = NULL;
	// *p = 1;

	// // example ： std:：count 测试
	// for(int i = 0;i <10; i++)
	// {
	// 	std::cout << i << std::endl;
	// }

	// // example ： inet_ntoa 测试
	// for(int i = -10; i <= 10; i++)
	// {
	// 	DWORD ip = i;
	// 	in_addr ia;
	// 	ia.s_addr = ip;
	// 	std::string strIP = inet_ntoa(ia);
	// 	std::cout << "ip=" << ip << ",strIP=" << strIP << std::endl;
	// }
	// for(int i = 65536; i <= 65546; i++)
	// {
	// 	DWORD ip = i;
	// 	in_addr ia;
	// 	ia.s_addr = ip;
	// 	std::string strIP = inet_ntoa(ia);
	// 	std::cout << "ip=" << ip << ",strIP=" << strIP << std::endl;
	// }

	// example : char* 赋值 string 测试
	// {
	// 	const char* pInfo = NULL;
	// 	std::string strInfo1 = pInfo;
	// 	std::cout << strInfo1 << std::endl;
	// }
	// 结论：
	// 实验证明不可以将一个 NULL 赋值给 string.

	// // example
	// std::string strInfo2 = "hello";
	// std::cout << strInfo2 << std::endl;

	// // example : 智能指针
	// std::shared_ptr<info> sp;
	// info* p = NULL;
	// sp.reset(p);
	// if(sp == NULL)
	// {
	// 	std::cout << "sp is NULL" << std::endl;
	// }
	// else
	// {
	// 	std::cout << "sp is valid" << std::endl;
	// }
	// p = new info(1);
	// sp.reset(p);
	// if(sp == NULL)
	// {
	// 	std::cout << "sp is NULL" << std::endl;
	// }
	// else
	// {
	// 	std::cout << "sp is valid" << std::endl;
	// }
	// auto *pList = new std::list<std::shared_ptr<info>>();
	// pList->push_back(sp);
	// std::cout << pList->size() << std::endl;
	// std::shared_ptr<info> sp2(new info(2));
	// pList->push_back(sp2);
	// std::cout << pList->size() << std::endl;
	// pList->pop_front();
	// std::cout << pList->size() << std::endl;
	// for(int i = 0; i < 10; i++)
	// {
	// 	std::shared_ptr<info> _sp(new info(i + 11));
	// 	pList->push_back(_sp);
	// }
	// while (!pList->empty())
	// {
	// 	/* code */
	// 	auto it = pList->front();
	// 	if(it)
	// 	{
	// 		std::cout << "info.id is " << it->GetID() << std::endl;
	// 	}
	// 	pList->pop_front();
	// 	sleep(1);
	// }
	// sleep(10);
	// delete pList;
}
