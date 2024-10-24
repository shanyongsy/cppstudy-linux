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
#include "stringopt.h"
#include "rename.h"

typedef unsigned long DWORD;

int main(int argc, char *argv[])
{
	TestVector();


	// TestTime();

	// test_init_int();

	// test_func_sort();

	// test_clear_vector();


	// test_list();

	// for(int i  = 0; i < 100; i++)
	// {
	// 	test_loop(i, 10);
	// }

	// std::string str = "hello";

	// str = "20240116";
	// std::cout << str << " is " << getDiffDay(str) << " days from now" << std::endl;

	// str = "20240117";
	// std::cout << str << " is " << getDiffDay(str) << " days from now" << std::endl;

	// str = "20240118";
	// std::cout << str << " is " << getDiffDay(str) << " days from now" << std::endl;

	// str = "20240119";
	// std::cout << str << " is " << getDiffDay(str) << " days from now" << std::endl;

	// str = "202402190";
	// std::cout << str << " is " << getDiffDay(str) << " days from now" << std::endl;


	// test_shop();

	// std::string str = "hello";

	// str = "20240116";
	// std::cout << str << " is " << getDiffDay(str) << " days from now" << std::endl;

	// str = "20240117";
	// std::cout << str << " is " << getDiffDay(str) << " days from now" << std::endl;

	// str = "20240118";
	// std::cout << str << " is " << getDiffDay(str) << " days from now" << std::endl;

	// str = "20240119";
	// std::cout << str << " is " << getDiffDay(str) << " days from now" << std::endl;

	// str = "202402190";
	// std::cout << str << " is " << getDiffDay(str) << " days from now" << std::endl;


	// str = "ab";
	// std::cout << str << " is " << getDiffDay(str) << " days from now" << std::endl;

	// str = "中国";
	// std::cout << str << " is " << getDiffDay(str) << " days from now" << std::endl;



	//find_str();


	// str_cmp_time();

	// make_mac();



	// NPC_NORMAL_SYNC npc1;
	// NPC_NORMAL_SYNC npc2 = npc1;
	// //npc2.MapX++;
	// if(npc1 != npc2)
	// {
	// 	std::cout << "npc1 != npc2" << std::endl;
	// }
	// else
	// {
	// 	std::cout << "npc1 == npc2" << std::endl;
	// }

	// int m_nNpcSyncCounter = 0;
	// int m_nMaxCount = 10;
	// for(int i = 0; i < 100; i++)
	// {
	// 	int nCounter = 0;
	// 	int nPoint = 0;
	// 	while (nPoint < m_nMaxCount)
	// 	{			
	// 		if((nCounter == m_nNpcSyncCounter /2) && (m_nNpcSyncCounter % 2 == 0))
	// 		{
	// 			std::cout << "yes";
	// 		}
	// 		else
	// 		{
	// 			std::cout << "no";
	// 		}
	// 		std::cout 
	// 			<< "\tnPoint=" << nPoint 
	// 			<< "\tnNpcSyncCounter=" << m_nNpcSyncCounter 
	// 			<< "\tvalue0=" << (m_nNpcSyncCounter /2)
	// 			<< "\tvalue1=" << (nCounter == m_nNpcSyncCounter /2)
	// 			<< "\tvalue2=" << (m_nNpcSyncCounter % 2)
	// 			<< std::endl;
	// 		nPoint++;
	// 		nCounter++;
	// 	}
	// 	m_nNpcSyncCounter++;
	// 	if(m_nNpcSyncCounter > m_nMaxCount *2)
	// 	{
	// 		m_nNpcSyncCounter = 0;
	// 	}
	// }

	// for(int i = 0; i < 10; i++)
	// {
	// 	if(i == 5)
	// 		if( i < 6) 
	// 			continue;
	// 	std::cout << "1-" << i << std::endl;
	// }

	// PlayerInfo info("小明", 1000);
	// for(int i = 0; i < 10; i++)
	// info.PrintFuncName(std::to_string(i));

	// example_func_name();

	// example_frame();
	// example_map();

	// compare
	// animal_att a1{1, 4};
	// animal_att a2{1, 0};
	// if( a1 != a2)
	// {
	// 	std::cout << "a1 != a2" << std::endl;
	// }
	// else
	// {
	// 	std::cout << "a1 == a2" << std::endl;
	// }
	// a1 = a2;
	// if( a1 != a2)
	// {
	// 	std::cout << "a1 != a2" << std::endl;
	// }
	// else
	// {
	// 	std::cout << "a1 == a2" << std::endl;
	// }


	// test ostringstream
	// {
	// 	std::ostringstream os;
	// 	os << "hello" << "world" << "!";
	// 	std::cout << os.str() << std::endl;

	// 	os.str("");
	// 	if( os.str().size() == 0)
	// 	{
	// 		std::cout << "os.str().size() == 0" << std::endl;
	// 	}
	// 	else
	// 	{
	// 		std::cout << "os.str().size() != 0" << std::endl;

	// 	}
	// 	std::cout << os.str() << std::endl;
	// }
	


	//test_sum();

	// rename_all_file();

	// example : signal
	//example_signal_handler_register();

	//fsb_MapToPoint(51936,102656);

	// g_GetLocalTimeString(0);
	// g_GetLocalTimeString(-1);
	// time_t long_time;
	// time( &long_time ); 
	// g_GetLocalTimeString(long_time);
	// long_time += 3600;
	// g_GetLocalTimeString(long_time);

	//id_level_value();

	//test_reportmsg();

	// test key_value_to_string
	// {
	// 	std::cout << key_value_to_string(std::string("name").c_str(), "sy")
	// 	<< key_value_to_string("name1", "sy")
	// 	<< key_value_to_string("name2", "sy")
	// 	<< key_value_to_string("age", 18)
	// 	<< key_value_to_string("value", 16.7)
	// 	<< key_value_to_string("姓名", "单勇")
	// 	<< key_value_to_string("国家", "中华人民共和国")
	// 	<< key_value_to_string("等级", 0, "");
	// }

	//test generateKeyValueString

	//std::cout << generateKeyValueString("name1", "sy", "nam2", "sy", "age", 18, "value", 16.7, "姓名", "单勇", "国家", "中华人民共和国", "等级", 0, "备注", 0.01) << std::endl;

	// std::string key1 = "name1";
	// std::string value1 = "sy";
	// std::string key2 = "name2";
	// std::string value2 = "sy";
	// std::string key3 = "age";
	// int value3 = 18;
	// std::string key4 = "value";
	// double value4 = 16.7;
	// std::string key5 = "姓名";
	// std::string value5 = "单勇";
	// std::cout << generateKeyValueString(
	// 	key1, "sy", 
	// 	key2, value2, 
	// 	key3, value3, 
	// 	key4, value4, 
	// 	key5, value5) 
	// 	<< std::endl;

	// std::cout << generateKeyValueString("na", value1, key2, 0, key3, value3, key4, value4, key5, value5) << std::endl;


	// example : mac to hex string
	// test_mac_to_hex_string();

	// example : system
	// example_system();

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
	// char c1[] = "123456789";
	// std::string strlog = "";
	// strlog.append(c1, 5);
	// std::cout << strlog << std::endl;
	// char c2[6] = {};
	// strncpy(c2, c1, sizeof(c2) - 1);
	// c2[5] = '\0';
	// std::string strInfo2 = c2;
	// std::cout << "strInfo2 = " << strInfo2 << std::endl;
	// std::string strInfo1 = c1;
	// std::cout << "strInfo1 = " << strInfo1 << std::endl;
	// std::cout << strlen(c1) << std::endl;
	// std::cout << strlen(c2) << std::endl;

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

	// example : 智能指针
	// std::shared_ptr<Info> sp;
	// Info* p = NULL;
	// sp.reset(p);
	// if(sp == NULL)
	// {
	// 	std::cout << "sp is NULL" << std::endl;
	// }
	// else
	// {
	// 	std::cout << "sp is valid" << std::endl;
	// }
	// p = new Info(1, "1");
	// sp.reset(p);
	// if(sp == NULL)
	// {
	// 	std::cout << "sp is NULL" << std::endl;
	// }
	// else
	// {
	// 	std::cout << "sp is valid" << std::endl;
	// }
	// auto *pList = new std::list<std::shared_ptr<Info>>();
	// pList->push_back(sp);
	// std::cout << pList->size() << std::endl;
	// std::shared_ptr<Info> sp2(new Info(2, "2"));
	// pList->push_back(sp2);
	// std::cout << pList->size() << std::endl;
	// pList->pop_front();
	// std::cout << pList->size() << std::endl;
	// for(int i = 0; i < 10; i++)
	// {
	// 	std::shared_ptr<Info> _sp(new Info(i + 11, std::to_string(i + 11)));
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
