#include <iostream>
#include <arpa/inet.h>
#include <memory>
#include <string>
#include "string.h"
#include <list>
#include <unistd.h>//sleep
#include <thread>
#include <pthread.h>

#include "version.h"
#include "func_declare.h"
#include "struct_def.h"
#include "memory"

typedef unsigned long DWORD;

int main(int argc, char *argv[])
{
	// example : version
	if(argc >= 2)
	{
		std::string in = argv[1];
		if(in == "--version")
		{
			// std::cout <<  PROJECT_VERSION << std::endl;
			std::cout <<  PROGRAM_VERSION << std::endl;
		}
	}

	// example : auto ptr
	std::shared_ptr<PlayerInfo> sp(new PlayerInfo("小明", 1000));
	// sp.reset();
	weakptr_example(sp);
	sleep(300);

	// // example : argc argv
	// std::cout << argc << std::endl;
	// for(int i = 0; i < argc; i++)
	// {
	// 	std::cout << argv[i] << std::endl;
	// }

	// // example : thread
	// // ps: g++ helloworld.cpp -lpthread
	// std::thread t(tf);
	// t.join();

	// // example : strncpy 测试
	// char c1[] = "1234567890abcdefg";
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
