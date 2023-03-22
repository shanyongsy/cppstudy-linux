#include "func_declare.h"
#include "struct_def.h"
#include <iostream>

void weakptr_example(std::weak_ptr<player_info> p)
{
    std::shared_ptr<player_info> sp_a = p.lock();
    if (sp_a) {
        std::cout 
        << "name\t: " << sp_a->name << std::endl
        << "id\t: " << sp_a->id << std::endl;
    }
}

void tf()
{
	std::cout << "tf" << std::endl;
};
