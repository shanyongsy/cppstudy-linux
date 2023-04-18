#include "system.h"
#include "stdlib.h"
#include "iostream"
#include "string"

void example_system()
{
    // int n = system("apt update");
    std::string strCommandLine;

    strCommandLine = std::string("c:\\python\\baidu.com");
    system(strCommandLine.c_str());
    std::cout << "ok" << std::endl;
}
