#include "func_declare.h"
#include "struct_def.h"
#include <iostream>

void example_weakptr(std::weak_ptr<PlayerInfo> p)
{
    std::shared_ptr<PlayerInfo> sp_a = p.lock();
    if (sp_a) {
        std::cout 
        << "name\t: " << sp_a->GetName() << std::endl
        << "id\t: " << sp_a->GetID() << std::endl;
    }
}

void example_tf()
{
	std::cout << "example_tf" << std::endl;
};

void example_sighandler(int signum)
{
    std::cout << "example_sighandler, signum=" << signum << std::endl; 
    exit(0);
}
