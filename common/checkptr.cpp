#include "func_declare.h"
#include "struct_def.h"
#include <iostream>

void weakptr_example(std::weak_ptr<PlayerInfo> p)
{
    std::shared_ptr<PlayerInfo> sp_a = p.lock();
    if (sp_a) {
        std::cout 
        << "name\t: " << sp_a->GetName() << std::endl
        << "id\t: " << sp_a->GetID() << std::endl;
    }
}

void tf()
{
	std::cout << "tf" << std::endl;
};
