#ifndef INFO_H
#define INFO_H

#include <string>
#include <iostream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>

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

struct  SkillInfo
{
    int16_t id{0};
    int32_t cd{0};
};

struct BHMJ_Challenge_Score
{
    char m_PlayerName[3][32];
    uint16_t m_nUseTime;    // 用时
    uint64_t m_nTimestamp;  // 记录的时间戳
    uint16_t m_nSeason;     // 赛季ID
    uint8_t m_nTurn;        // 轮次
    uint8_t m_nLayer;       // 层次

    BHMJ_Challenge_Score() {
        std::memset(m_PlayerName, 0, sizeof(m_PlayerName));
        m_nUseTime = 0;
        m_nTimestamp = 0;
        m_nSeason = 0;
        m_nTurn = 0;
        m_nLayer = 0;
    }

    // 排序函数：按字典序升序
    void sortNames() {
        // 1. 临时拷贝到 std::array
        std::array<std::array<char, 32>, 3> temp;
        for (int i = 0; i < 3; ++i) {
            std::memcpy(temp[i].data(), m_PlayerName[i], 32);
        }

        // 2. 排序
        std::sort(temp.begin(), temp.end(),
            [](const auto& a, const auto& b) {
                return std::strcmp(a.data(), b.data()) < 0;
            });

        // 3. 写回到 m_PlayerName
        for (int i = 0; i < 3; ++i) {
            std::memcpy(m_PlayerName[i], temp[i].data(), 32);
        }
    }

    void printNames() const {
        int nIndex = 0;
        for (const auto &name : m_PlayerName) {
            if (name[0] != '\0')
                std::cout << std::to_string(nIndex) << ":" << name << std::endl;
            else
                std::cout << std::to_string(nIndex) << ":" << std::endl;

            nIndex++;
        }
    }

    // 覆盖某个玩家名字
    void setPlayerName(int index, const char* name) {
        if (index < 0 || index >= 3) {
            std::cerr << "Index out of range: " << index << "\n";
            return;
        }
        // 先清空该槽位
        std::memset(m_PlayerName[index], 0, sizeof(m_PlayerName[index]));
        // 拷贝字符串，最多拷贝 31 个字符，保证末尾是 '\0'
        std::strncpy(m_PlayerName[index], name, sizeof(m_PlayerName[index]) - 1);
    }

    std::string getKey() const {
        std::string key;
        for (size_t i = 0; i < 3; ++i) {
            key += std::string(m_PlayerName[i]);
            if (i < 2) key += "_"; // 在名字之间加入下划线
        }
        return key;
    }
};

#endif // INFO_H
