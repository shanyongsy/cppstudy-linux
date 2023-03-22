#pragma once

#include <string>
#include <iostream>

class info
{
private:
    const int id;
    const std::string name;
public:
    info(int _id, const std::string& _name) : id(_id), name(_name) {}
    info() : id(0), name("") {}
    ~info(){ std::cout << "~info(), id is " << this->id << std::endl; };
public:
    int GetID() const { return id; }
    const std::string& GetName() const { return name; }
};

struct player_info
{
    /* data */
    std::string name;
    int id;
};