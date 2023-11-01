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
    void PrintFuncName(std::string name) const { 
        static const std::string funcName = name + __FUNCTION__;
        std::cout << "func: " << funcName << std::endl; }
};

struct animal
{
    std::string name;
    int legs;
};

struct animal_att
{
    int32_t id;
    int32_t age;

    bool operator!=(const animal_att& rhs) const
    {
        return memcmp(this, &rhs, sizeof(animal_att)) != 0;
    }

};

struct NPC_NORMAL_SYNC
{
    uint8_t ProtocolType;
    // Add by Cooler -->
    // 2005-9-27
    uint8_t bInWar;
    uint8_t byWarCamp;
    // End add by Cooler <--
    uint8_t Camp; // 阵营有一部分用来表示生命百分比了,所以阵营最多只支持32种 lixuewu 2004.11.17
    uint32_t ID;
    uint32_t MapX;
    uint32_t MapY;
    // Rocker 2004.6.15
    uint32_t insideSiegeWeaponID; // 如果驻扎状态，那么就是驻扎的攻城武器ID
    // Rocker 2004.6.15
    uint8_t LifePerCent;
    uint8_t Doing;
    uint8_t State;
    // Add by Cooler -->
    // 2005-10-20
    uint8_t byWarDuty;
    // End add by Cooler <--
    uint8_t movelock;

public:
    bool operator!=(const NPC_NORMAL_SYNC& rhs) const
    {
        return memcmp(this, &rhs, sizeof(NPC_NORMAL_SYNC)) != 0;
    }
};

#endif // INFO_H
