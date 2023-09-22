#ifndef INFO_H
#define INFO_H

#include <string>
#include <iostream>

class Info
{
private:
    const int id;
    const std::string name;

public:
    Info(int _id, const std::string &_name) : id(_id), name(_name) {
        std::cout << __FUNCTION__ << std::endl;
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~Info() { 
        std::cout << __FUNCTION__ << std::endl;
        std::cout << __PRETTY_FUNCTION__ << std::endl;  
        std::cout << "id is " << this->id << std::endl; 
        };

public:
    int GetID() const { 
        std::cout << __FUNCTION__ << std::endl;
        std::cout << __PRETTY_FUNCTION__ << std::endl;  
        return id; 
        }
    const std::string &GetName() const { return name; }
};

class PlayerInfo
{
private:
    const std::string name;
    const int id;

public:
    PlayerInfo(const std::string &_name, int _id) : name(_name), id(_id) {}

public:
    int GetID() const { return id; }
    const std::string &GetName() const { return name; }
};

struct animal
{
    std::string name;
    int legs;
};

#endif // INFO_H
