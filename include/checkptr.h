#include <string>
#include <memory>

struct player_info
{
    /* data */
    std::string name;
    int id;
};

void weakptr_example(std::weak_ptr<player_info> p);


