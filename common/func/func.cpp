#include <iostream>
#include <csignal>
#include <cstring>
#include <sstream>
#include <vector>
#include <cassert>
#include <cstdarg>
#include <chrono>
#include <iostream>
#include <thread>
#include <algorithm>
#include <map>
#include <list>

#include <iostream>
#include <random>

#include <ctime>
#include <iomanip>

#include "func.h"
#include "struct_def.h"
#include "md5c.h"

static uint32_t nRandomSeed = 0;

uint64_t g_Random(uint64_t nMax)
{
	if (nMax)
	{
		nRandomSeed = nRandomSeed * 214013L + 2531011L;
		return ((nRandomSeed >> 16) & 0x7fff) % nMax;
	}
	else
	{
		return 0;
	}
}

void test_random()
{
    nRandomSeed = time(0);
    for(int i = 0; i < 10; i++)
    {
        int nCount_70 = 0;
        int nCount_80 = 0;
        int nCount_90 = 0;

        for(int j = 0; j < 10; j++)
        {
            int nRandomValue = g_Random(100);
            if(nRandomValue < 70)
            {
                nCount_70++;
            }
            
            if(nRandomValue < 80)
            {
                nCount_80++;
            }
            
            if(nRandomValue < 90)
            {
                nCount_90++;
            }
            
            std::cout << g_Random(100) << " ";
        }

        std::cout << std::endl;

        std::cout << "70:" << std::to_string(nCount_70) 
        << ",80:" << std::to_string(nCount_80)
        << ",90:" << std::to_string(nCount_90) 
        << std::endl << std::endl;
    }
}

void TestVector2()
{
    // 定义节点结构
    struct KMergeListNode {
        std::string name = "";  // 显示名称
        int id = 0;             // 原配方中的ID
        int count = 0;          // 可合成数量
        std::vector<int> vItems;  // 合成所需物品
    };

    std::vector<KMergeListNode> vNodes = {
        {"NodeA", 3, 5, {1, 2, 3, 10, 20, 30}},
        {"NodeB", 1, 10, {4, 5, 6}},
        {"NodeC", 2, 5, {7, 8, 9}},
        {"NodeD", 4, 10, {10, 11, 12}},
        {"NodeE", 5, 3, {13, 14, 15}}
    };

    KMergeListNode node = vNodes[0];
    std::cout 
    << "Name: " << node.name 
    << ", ID: " << node.id 
    << ", Count: " << node.count 
    << ", Items: " << node.vItems.size()
    << '\n';

    // 使用 lambda 表达式排序
    std::sort(vNodes.begin(), vNodes.end(), [](const KMergeListNode& a, const KMergeListNode& b) {
        if (a.count != b.count) {
            return a.count > b.count;  // 优先按照 count 降序
        }
        return a.id < b.id;  // 然后按照 id 升序
    });

    // 输出结果
    for (const auto& node : vNodes) {
        std::cout << "Name: " << node.name << ", ID: " << node.id << ", Count: " << node.count << '\n';
    }



    
}

void TestVector()
{
    std::vector<SkillInfo> vInfo;
    for(int i = 0; i < 10; i++)
    {
        SkillInfo info;
        info.id = i;
        info.cd = i;
        vInfo.push_back(info);
    }
    
    int nCount = vInfo.size();
    int nLen = sizeof(SkillInfo) * nCount;
    char* pBuff = new char[nLen];
    memset(pBuff, 0, nLen);
    
    SkillInfo* pInfo = (SkillInfo*)pBuff;
    for(int i = 0; i < nCount; i++)
    {
        pInfo[i] = vInfo[i];
    }
    vInfo.clear();

    for(int i = 0; i < nCount; i++)
    {
        std::cout << "id=" << pInfo[i].id << ",cd=" << pInfo[i].cd << std::endl;
    }

    delete[] pBuff;
}

// 测试时间与 uint32_t 的转换，以及时间的同天判断
void TestTime()
{
    time_t tNow = time(0);
    uint32_t nNow = static_cast<uint32_t>(tNow);
    time_t tUse = static_cast<time_t>(nNow);
    tm* tmNow = localtime(&tUse);
    std::cout << (tmNow->tm_year + 1900) << '-' << (tmNow->tm_mon + 1) << '-' << tmNow->tm_mday << ' ' << tmNow->tm_hour << ':' << tmNow->tm_min << ':' << tmNow->tm_sec << std::endl;

    for(int i  = 0 ; i < 24 ; i++)
    {
        nNow += 60 * 60;
        time_t tTemp = static_cast<time_t>(nNow);
        tm* tmTemp = localtime(&tTemp);
        std::cout << (tmTemp->tm_year + 1900) << '-' << (tmTemp->tm_mon + 1) << '-' << tmTemp->tm_mday << ' ' << tmTemp->tm_hour << ':' << tmTemp->tm_min << ':' << tmTemp->tm_sec << std::endl;

        bool b = IsSameDay(tNow, tTemp);
        std::string str = b ? "yes" : "no";
        std::cout << "same day = " << str.c_str() << std::endl;
    }
}

// 是否是同一天
bool IsSameDay(time_t nTm1, time_t nTm2)
{
    tm tTime1;
    tm tTime2;
    localtime_r(&nTm1, &tTime1);
    localtime_r(&nTm2, &tTime2);
    return tTime1.tm_year == tTime2.tm_year && tTime1.tm_yday == tTime2.tm_yday;
}

// 获取指定时间戳的当天零时时间戳
time_t GetZeroTm(time_t nTm)
{
    tm tTime;
    localtime_r(&nTm, &tTime);
    tTime.tm_hour = 0;
    tTime.tm_min = 0;
    tTime.tm_sec = 0;
    return mktime(&tTime);
}

void test_init_int()
{
    int value[3] = {-1};
    for(int i = 0; i < 3; i++)
    {
        std::cout << value[i] << std::endl;
    }
}

void test_func_sort()
{
    std::cout << "test_func_sort" << std::endl;

    int value[3] = {3,1,2};
    std::sort(value, value + 3);

    for(int i = 0; i < 3; i++)
    {
        std::cout << value[i] << std::endl;
    }
}

struct STATE_EFFECT_SYNC
{
    int32_t nEffectID;
    int32_t nEffectLevel;
    int32_t nForce;
    int32_t nEffectTime;
};

void test_clear_vector()
{
    STATE_EFFECT_SYNC info[10];
    for(int i = 0; i < 10; i++)
    {
        info[i].nEffectID = i;
        info[i].nEffectLevel = 1;
        info[i].nForce = 1;
        info[i].nEffectTime = 1;
    }
    std::cout << "size=" << sizeof(STATE_EFFECT_SYNC) << std::endl;
    std::cout << "size=" << sizeof(info) << std::endl;
    memset(info, 0, sizeof(info));
    for(int i = 0; i < 10; i++)
    {
        std::cout << "id=" << info[i].nEffectID << std::endl;
    }


    // {
    //     int32_t nValue = 7;
    //     // 求与 4 的商
    //     int32_t nDivResult = nValue / 4;
    //     // 求与 4 的余数
    //     int32_t nModResult = nValue % 4;
    //     std::cout << "nDivResult=" << nDivResult << std::endl;
    //     std::cout << "nModResult=" << nModResult << std::endl;
    // }



}

 std::list<STATE_EFFECT_SYNC> lsValue;

void AddEffect(STATE_EFFECT_SYNC &sync)
{
    if(sync.nForce > 0)
	{// 删除所有相同  skill id 的信息				
		for (std::list<STATE_EFFECT_SYNC>::iterator it = lsValue.begin(); it != lsValue.end();)
		{
			if (it->nEffectID == sync.nEffectID)
			{
                std::cout << "erase " << "id=" << it->nEffectID << std::endl;
				it = lsValue.erase(it);
			}
            else
            {
                ++it;
            }
		}
	}
	else
	{// 查询最后一个相同 skill id 的数据信息
		std::list<STATE_EFFECT_SYNC>::iterator lastIt = lsValue.end();
		for (std::list<STATE_EFFECT_SYNC>::iterator it = lsValue.begin(); it != lsValue.end(); ++it)
		{
			if(it->nEffectID == sync.nEffectID)
			{
				lastIt = it;
			}
		}

		if(lastIt != lsValue.end())
		{
			if(lastIt->nForce <= 0 )
			{
				if(lastIt->nEffectLevel <= sync.nEffectLevel)
				{
                    std::cout << "erase " << "id=" << lastIt->nEffectID << std::endl;
					lsValue.erase(lastIt);
				}
				else
				{
                    std::cout << "pass " << "id=" << sync.nEffectID << std::endl;
					return;
				}
			}
		}
	}	

	lsValue.push_back(sync);
}

void test_list()
{
    for (int i = 0; i < 10; i++)
    {
        STATE_EFFECT_SYNC info;
        info.nEffectID = i;
        info.nEffectLevel = 3;
        info.nForce = 1;
        AddEffect(info);
    }    

    STATE_EFFECT_SYNC info;
    info.nEffectID = 5;
    info.nEffectLevel = 4;
    info.nForce = 1;
    AddEffect(info);    
    // 轮询打印
    for (std::list<STATE_EFFECT_SYNC>::iterator it = lsValue.begin(); it != lsValue.end(); ++it)
    {
        std::cout << "id=" << it->nEffectID << ",level=" << it->nEffectLevel << ",force=" << it->nForce << std::endl;
    }
    std::cout <<  "-------------------" << std::endl;

    info.nEffectID = 5;
    info.nEffectLevel = 5;
    info.nForce = 0;
    AddEffect(info);    
    // 轮询打印
    for (std::list<STATE_EFFECT_SYNC>::iterator it = lsValue.begin(); it != lsValue.end(); ++it)
    {
        std::cout << "id=" << it->nEffectID << ",level=" << it->nEffectLevel << ",force=" << it->nForce << std::endl;
    }
    std::cout <<  "-------------------" << std::endl;

    info.nEffectID = 5;
    info.nEffectLevel = 1;
    info.nForce = 0;
    AddEffect(info);    
    // 轮询打印
    for (std::list<STATE_EFFECT_SYNC>::iterator it = lsValue.begin(); it != lsValue.end(); ++it)
    {
        std::cout << "id=" << it->nEffectID << ",level=" << it->nEffectLevel << ",force=" << it->nForce << std::endl;
    }
    std::cout <<  "-------------------" << std::endl;

    info.nEffectID = 5;
    info.nEffectLevel = 6;
    info.nForce = 0;
    AddEffect(info);    
    // 轮询打印
    for (std::list<STATE_EFFECT_SYNC>::iterator it = lsValue.begin(); it != lsValue.end(); ++it)
    {
        std::cout << "id=" << it->nEffectID << ",level=" << it->nEffectLevel << ",force=" << it->nForce << std::endl;
    }
    std::cout <<  "-------------------" << std::endl;

    info.nEffectID = 5;
    info.nEffectLevel = 2;
    info.nForce = 1;
    AddEffect(info);    
    // 轮询打印
    for (std::list<STATE_EFFECT_SYNC>::iterator it = lsValue.begin(); it != lsValue.end(); ++it)
    {
        std::cout << "id=" << it->nEffectID << ",level=" << it->nEffectLevel << ",force=" << it->nForce << std::endl;
    }
    std::cout <<  "-------------------" << std::endl;

    info.nEffectID = 1;
    info.nEffectLevel = 2;
    info.nForce = 0;
    AddEffect(info);    
    // 轮询打印
    for (std::list<STATE_EFFECT_SYNC>::iterator it = lsValue.begin(); it != lsValue.end(); ++it)
    {
        std::cout << "id=" << it->nEffectID << ",level=" << it->nEffectLevel << ",force=" << it->nForce << std::endl;
    }
    std::cout <<  "-------------------" << std::endl;



}

void test_loop(int loop_count, int data_length)
{
    // std::cout << "loop_count = " << loop_count << std::endl;
    // std::cout << "data_length = " << data_length << std::endl;

    static int32_t m_nNpcSyncCounter = 0;
    int	nCounter = 0;
    int nNpcCurSyncIdx = m_nNpcSyncCounter / 2;
	int nNpcModResult = m_nNpcSyncCounter & 1;

    int32_t nNodeIndex = 0;
    while (nNodeIndex < data_length)
    {
        if ( nNpcModResult == 0 && nNpcCurSyncIdx == nCounter )
		{
            std::cout << "loop=" << loop_count << ",index=" << nNodeIndex << ",counter=" << nCounter << ",nNpcSyncCounter=" << m_nNpcSyncCounter << std::endl;
		}
        nCounter++;
        nNodeIndex++;
    }
	m_nNpcSyncCounter++;
	if (m_nNpcSyncCounter > data_length * 3)
	{
		m_nNpcSyncCounter = 0;
	}
	nCounter = 0;
}
void test_shop()
{
    const int price_4 = 4;
    const int price_3 = 3;
    const int price_2 = 2;
    const int price_1 = 1;
    const int price_total = 10;

    std::cout << "1元" << "\t" << "2元" << "\t" << "3元" << "\t" << "4元" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for(int i_1 = 0; i_1 <= 10; i_1++)
    {
        for(int i_2 = 0; i_2 <= 10; i_2++)
        {
            for(int i_3 = 0; i_3 <= 10; i_3++)
            {
                for(int i_4 = 0; i_4 <= 10; i_4++)
                {
                    int count = i_1 + i_2 + i_3 + i_4;
                    int price = i_1 * price_1 + i_2 * price_2 + i_3 * price_3 + i_4 * price_4;
                    if(count == 4 && price == 10)
                    {
                        std::cout << i_1 << "\t" << i_2 << "\t" << i_3 << "\t" << i_4 << std::endl;
                    }
                }
            }
        }
    }
}

bool isValidDateString(const std::string& dateStr) {
    std::tm tm = {0};
    return std::sscanf(dateStr.c_str(), "%4d%2d%2d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday) == 3;
}

// return : 1 今天
//          <= 0 过去
int32_t getDiffDay(std::string dateStr)
{
    // 检查日期字符串的有效性
    if (!isValidDateString(dateStr)) {
        // std::cerr << "无效的日期字符串格式" << std::endl;
        return -1000;
    }

    // 获取当前日期的零点
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    struct std::tm* timeinfo = std::localtime(&now_time);
    timeinfo->tm_hour = 0;
    timeinfo->tm_min = 0;
    timeinfo->tm_sec = 0;
    auto todayStart = std::chrono::system_clock::from_time_t(std::mktime(timeinfo));

    // 从字符串解析目标日期
    int year, month, day;
    std::sscanf(dateStr.c_str(), "%4d%2d%2d", &year, &month, &day);

    // 设置目标日期
    std::tm targetDate = {0};
    targetDate.tm_year = year - 1900;
    targetDate.tm_mon = month - 1;
    targetDate.tm_mday = day;

    // 计算天数差异
    auto targetPoint = std::chrono::system_clock::from_time_t(std::mktime(&targetDate));
    std::chrono::system_clock::duration daysDifference = targetPoint - todayStart;

    // 输出结果
    int32_t ret =  std::chrono::duration_cast<std::chrono::hours>(daysDifference).count() / 24 ;
    ret++;
    return ret;
}

void find_str()
{
    std::string strInfo = "Hello<c=y>World";

    // 查找子字符串
    size_t found = strInfo.find("<c=y>");

    std::cout << found << std::endl;

    // 检查是否找到
    if (found != std::string::npos) {
        std::cout << "字符串包含子字符串 \"<c=y>\"" << std::endl;
    } else {
        std::cout << "字符串不包含子字符串 \"<c=y>\"" << std::endl;
    }
}

void make_mac()
{
    char m_szLoginMAC[6];
    m_szLoginMAC[0] = 0xaa;
    m_szLoginMAC[1] = 0xbb;
    m_szLoginMAC[2] = 0xcc;
    m_szLoginMAC[3] = 0xdd;
    m_szLoginMAC[4] = 0xaa;
    m_szLoginMAC[5] = 0xb1;

    {
        std::string mac = "";
        for (int i = 0; i < 6; i++)
        {
            char szTemp[10] = {0};
            sprintf(szTemp, "%02X", static_cast<unsigned char>(m_szLoginMAC[i]));
            mac += szTemp;
        }
        
            std::cout << mac << std::endl;
    }

    {
        std::string    mac = "";
        char szTemp[32] = {0};
        sprintf(szTemp, "%02x%02x%02x%02x%02x%02x",  
        static_cast<unsigned char>(m_szLoginMAC[0]), 
        static_cast<unsigned char>(m_szLoginMAC[1]), 
        static_cast<unsigned char>(m_szLoginMAC[2]), 
        static_cast<unsigned char>(m_szLoginMAC[3]), 
        static_cast<unsigned char>(m_szLoginMAC[4]), 
        static_cast<unsigned char>(m_szLoginMAC[5]));
        mac = szTemp;

        std::cout << mac << std::endl;
    }
}

void str_cmp_time()
{
const int numStrings = 5000;

    // Generate 1w random UUIDs
    std::map<std::string,std::string> uuids;

    for (int i = 0; i < numStrings; ++i) {
        uuids[generateRandomUUID()] = generateRandomUUID();
        // uuids.push_back(generateRandomUUID());
    }

    // Pick a random string to compare against
    std::string stringToCompare = generateRandomUUID();

    // Measure the time for string comparison
    auto startTime = std::chrono::high_resolution_clock::now();

    for (const auto& uuid : uuids) {
        if (uuid.second == stringToCompare) {
            // Do something with the matching string (optional)
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    std::cout << "Time taken for comparison: " << duration.count() << " microseconds" << std::endl;


    std::string str1 = " he llo  ";
    str1.erase(0, str1.find_first_not_of(" "));

    std::cout << "|" << str1 << "|" << std::endl;


}

std::string generateRandomUUID() {
    static const char hexChars[] = "0123456789ABCDEF";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    std::string uuid = "D4ED8B20-486A-3C8F-16EC-";
    for (int i = 0; i < 12; ++i) {
        if (i == 8 || i == 13) {
            uuid += '-';
        } else {
            uuid += hexChars[dis(gen)];
        }
    }

    return uuid;
}

void example_func_name()
{
    std::string str = __func__;
    std::cout << str << std::endl;

    std::string str1 = __FUNCTION__;
    std::cout << str1 << std::endl;

    std::string str2 = __PRETTY_FUNCTION__;
    std::cout << str2 << std::endl;
}

void example_map()
{
    std::map<int, int*> myMap;
    
    int value1 = 42;
    int value2 = 123;

    myMap[1] = &value1;
    myMap[2] = &value2;

    auto it = myMap.find(1);

    if (it != myMap.end()) {
        // 删除 it 指向的元素
        myMap.erase(it);

        // it->second 仍然有效，指向原始的 value1 指针
        std::cout << *(it->second) << std::endl;
    }
}

void example_frame()
{
    int frameCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    // 模拟一些帧的处理，此处可替换为实际的游戏逻辑
    for (int i = 0; i < 1000; ++i) {
        // 处理帧的逻辑

        // 帧计数增加
        frameCount++;

        // 在此处模拟帧处理的时间间隔，可以根据实际需要调整
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // 模拟每帧16毫秒
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;

    // 计算帧率
    auto count = duration.count();
    double fps = frameCount / count;

    // 打印帧率
    std::cout << "帧率: " << fps << " FPS" << std::endl;
}

void example_frame_2()
{
    const double samplingPeriod = 1.0;  // 采样周期为1秒
    int frameCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    bool frameDelayed = false;

    while (true) {
        auto frameStartTime = std::chrono::high_resolution_clock::now();

        // 模拟帧处理
        // 这里可以是实际的游戏逻辑

        auto frameEndTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> frameDuration = frameEndTime - frameStartTime;

        if (frameDuration.count() > samplingPeriod) {
            frameDelayed = true;
        }

        frameCount++;

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - startTime;

        if (elapsedTime.count() >= samplingPeriod) {
            double fps = frameDelayed ? 0 : frameCount / samplingPeriod;
            std::cout << "帧率: " << fps << " FPS" << std::endl;
            startTime = currentTime;
            frameCount = 0;
            frameDelayed = false;
        }
    }
}

void example_weakptr(std::weak_ptr<PlayerInfo> p)
{
    std::shared_ptr<PlayerInfo> sp_a = p.lock();
    if (sp_a)
    {
        std::cout
            << "name\t: " << sp_a->GetName() << std::endl
            << "id\t: " << sp_a->GetID() << std::endl;
    }
}

void example_tf()
{
    std::cout << "example_tf" << std::endl;
};

void signal_handler(int signum)
{
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;
    exit(signum);
}

void example_signal_handler_register()
{
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGKILL, signal_handler);
}

void calculate_md5_example()
{
    static const char *const test[7] = {
        "",                                                                                /*d41d8cd98f00b204e9800998ecf8427e*/
        "a",                                                                               /*0cc175b9c0f1b6a831c399e269772661*/
        "abc",                                                                             /*900150983cd24fb0d6963f7d28e17f72*/
        "message digest",                                                                  /*f96b697d7cb7938d525a2f31aaf161d0*/
        "abcdefghijklmnopqrstuvwxyz",                                                      /*c3fcd3d76192e4007dfb496cca67e13b*/
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",                  /*d174ab98d277d9f5a5611c2c9f419d9f*/
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890" /*57edf4a22be3c955ac49da2e2107b67a*/
    };

    int i;

    for (i = 0; i < 7; ++i)
    {
        md5_state_t state;
        md5_byte_t digest[16];
        int di;

        md5_init(&state);
        md5_append(&state, (const md5_byte_t *)test[i], std::strlen(test[i]));
        md5_finish(&state, digest);
        printf("MD5 (\"%s\") = ", test[i]);
        for (di = 0; di < 16; ++di)
            printf("%02x", digest[di]);
        printf("\n");
    }
}

void calculate_string_md5(const std::string &in, std::string &out)
{
    // init
    const int di = 16;
    md5_state_t state;
    md5_byte_t digest[di];

    // calculate
    md5_init(&state);
    md5_append(&state, (const md5_byte_t *)in.c_str(), std::strlen(in.c_str()));
    md5_finish(&state, digest);

    // out info
    {
        // printf("MD5 (\"%s\") = ", test[i]);
        // for (di = 0; di < 16; ++di)
        //     printf("%02x ", digest[di]);
        // printf("\n");

        out = "";
        // char buff_large[512] = {};
        // sprintf(buff_large, "MD5 (\"%s\") = ", in.c_str());
        // out.append(buff_large);
        for (int i = 0; i < di; ++i)
        {
            char buff_out[3] = {};
            sprintf(buff_out, "%02x", digest[i]);
            out.append(buff_out);
        }
    }
}

bool calculate_file_md5(const std::string &file, std::string &out)
{
    unsigned char ReadBuffer[65536];
    size_t ReadBytes = 0;
    md5_state_t state;
    const int di = 16;
    md5_byte_t digest[di];

    md5_init(&state);

    FILE *fp = fopen(file.c_str(), "rb");
    if (!fp)
        return false;

    while (true)
    {
        ReadBytes = fread(ReadBuffer, 1, 65536, fp);
        if (ReadBytes > 0)
            md5_append(&state, (const md5_byte_t *)ReadBuffer, ReadBytes);

        if (feof(fp))
        {
            md5_finish(&state, digest);
            break;
        }
    }
    fclose(fp);
    fp = NULL;

    // int i;
    // printf("File %s:\n", file.c_str());
    // printf("MD5 = ");
    // for (i = 0; i < 16; i++)
    //     printf("%02X ", digest[i]);
    // printf("\n");

    // print out
    {
        std::ostringstream oss;
        oss << "file " << file << ":" << std::endl;
        oss << "md5 = ";

        for (int i = 0; i < di; i++)
        {
            char buff_out[3] = {};
            sprintf(buff_out, "%02x", digest[i]);
            oss << buff_out;
        }

        oss << std::endl;
        out = oss.str();
    }

    return true;
}

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, delimiter))
    {
        result.push_back(token);
    }

    return result;
}

void split_string()
{
    if (false)
    {
        std::string str = "hello,world,how,are,you";
        std::vector<std::string> parts = split(str, ',');
        std::cout << str << std::endl;
        std::cout << parts.size() << std::endl;
        for (const auto &part : parts)
        {
            std::cout << part << std::endl;
        }
        std::cout << std::endl;
    }

    if (false)
    {
        std::string str = "";
        std::vector<std::string> parts = split(str, ',');
        std::cout << str << std::endl;
        std::cout << parts.size() << std::endl;
        for (const auto &part : parts)
        {
            std::cout << part << std::endl;
        }
        std::cout << std::endl;
    }

    if (false)
    {
        std::string str = "hello";
        std::vector<std::string> parts = split(str, ',');
        std::cout << str << std::endl;
        std::cout << parts.size() << std::endl;
        for (const auto &part : parts)
        {
            std::cout << part << std::endl;
        }
        std::cout << std::endl;
    }

    if (false)
    {
        std::vector<std::string> parts;
        std::cout << parts.empty() << std::endl;
        std::cout << parts.size() << std::endl;
    }

    {
        char info[] = "hello world";
        std::string s_info;
        s_info.assign(info, 32);
        std::cout << s_info.c_str() << std::endl;

        std::string s_info_short;
        s_info_short.assign(info, 3);
        std::cout << s_info_short << std::endl;
    }
}

std::string mac_to_hex_string(const char* value, size_t len) {

    std::cout << "len = " << len << std::endl;

    std::string hex_string;
    hex_string.resize(len * 2);

    std::sprintf(&hex_string[0], "%02x", static_cast<unsigned char>(value[0]));
    for (size_t i = 1; i < len; ++i) {
        std::sprintf(&hex_string[i * 2], "%02x", static_cast<unsigned char>(value[i]));
    }

    return hex_string;
}

void test_mac_to_hex_string()
{
    std::string mac = "1234567";
    std::string mac_hex = mac_to_hex_string(mac.c_str(), mac.size());
    std::cout << mac_hex << std::endl;

    const char* mac1 = "\x00\x11\x22\x33\x44\x55";
    const char* mac2 = "\xaa\xbb\xcc\xdd\xee\xff";
    const char* mac3 = "\x01\x23\x45\x67\x89\xab\xcd\xef";
    const char* mac4 = "中华人名共和国shi伟大的民族中华人名共和国shi伟大的民族";

    std::cout << mac_to_hex_string(mac1, sizeof(mac1)) << std::endl;
    std::cout << mac_to_hex_string(mac2, sizeof(mac2)) << std::endl;
    std::cout << mac_to_hex_string(mac3, sizeof(mac3)) << std::endl;
    std::cout << mac_to_hex_string(mac4, sizeof(mac4)) << std::endl;
}

#pragma	pack(push, 1)
struct CLIENT_EXTEND_HEADER
{
    unsigned char	ProtocolID;
    uint16_t	    wLength;
    unsigned char	ProtocalType;
    void	SetProtocolHeader(unsigned char byProtocol, uint16_t wLen)
    {
        ProtocolID = 190;
        ProtocalType = byProtocol;
        wLength = wLen;
    };
};

struct REPORT_MSG : CLIENT_EXTEND_HEADER
{
    unsigned char	reportLevel;		// REPORT_LEVEL
    unsigned char	reportType;			// REPORT_TYPE
    uint16_t	    msgSize;			// the size of msgContent
    char		    msgContent[0];

public:
    REPORT_MSG()
    {
        reportLevel = 0;
        reportType = 0;
        msgSize = 0;
    }
};
#pragma	pack(pop)

void report_msg(int level, int type, const char* content)
{
    // 模拟发送
    const size_t maxSendLength = 1024;
	const size_t nSendLength = strlen(content);
	if (nSendLength > maxSendLength - sizeof(REPORT_MSG) - 1)
		return;

	char szBuf[maxSendLength];
	std::memset(szBuf, 0, sizeof(szBuf));
	REPORT_MSG* sendMsg = (REPORT_MSG*)szBuf;

	sendMsg->reportLevel = (unsigned char)(level);
	sendMsg->reportType = (unsigned char)(type);
	sprintf(sendMsg->msgContent, "%s", content);
	sendMsg->msgSize = strlen(sendMsg->msgContent);

    size_t wLength = sizeof(REPORT_MSG) + sendMsg->msgSize + 1 - 1;
    sendMsg->SetProtocolHeader(80, wLength);
    const size_t nSendSize = wLength + 1;

    // 模拟接收
    char revBuf[maxSendLength];
    const size_t nRevSize = sizeof(REPORT_MSG) + sendMsg->msgSize + 1;

    assert(nSendSize == nRevSize);

    std::memcpy(revBuf, szBuf, nRevSize);
    REPORT_MSG* msg = (REPORT_MSG*)szBuf;
    std::cout << msg->msgContent << std::endl;

    char msgBuf[maxSendLength];
    std::memcpy(msgBuf, msg->msgContent, msg->msgSize);
    msgBuf[msg->msgSize] = '\0';
    std::cout << msgBuf << std::endl;
    
}

void test_reportmsg()
{
    char content[] = "[NpcSet.Add]Err.Reason=failed to findfree,kind=3,id=1822,setidx=12320769,x=47085,y=32097";
    char sendbuf[300];
    memset(sendbuf, 0, sizeof(sendbuf));
    sprintf(sendbuf, "%s", content);
    report_msg(11, 22, sendbuf);
}

typedef unsigned long       DWORD;
typedef unsigned short      WORD;
typedef unsigned int        UINT;
typedef unsigned int        UINT_PTR;
typedef unsigned long       ULONG_PTR;
typedef ULONG_PTR           DWORD_PTR;
typedef long LONG;

#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))

void id_level_value()
{
    int id = 979;
    int level = 1;

    int value = MAKELONG(level, id);
    std::cout << value << std::endl;
    printf("id=%4x\n", id);
    printf("level=%4x\n", level);
    printf("value=%4x\n", value);

    value  = 16187402;

    int id1 = HIWORD(value);
    int level1 = LOWORD(value);
    std::cout << id1 << std::endl;
    std::cout << level1 << std::endl;

}

std::string g_GetLocalTimeString(const time_t& t)
{
	struct tm* next_local_time = localtime(&t);
	int year = next_local_time->tm_year + 1900;     // Year since 1900
	int month = next_local_time->tm_mon + 1;        // Month (0-11)
	int day = next_local_time->tm_mday;             // Day of the month (1-31)
	int hour = next_local_time->tm_hour;            // Hours (0-23)
	int minute = next_local_time->tm_min;           // Minutes (0-59)
	int second = next_local_time->tm_sec;           // Seconds (0-59)

	std::ostringstream str;
	str << std::to_string(year) << ""
    << std::to_string(month) << ""
    << std::to_string(day) << ""
    << std::to_string(hour) << ""
    << std::to_string(minute) << ""
    << std::to_string(second);

    std::cout << str.str() << std::endl;

    return str.str();
}

void fsb_MapToPoint(int x, int y)
{
    int map_x = x / 32;
    int map_y = y / 32;

    int map_x1 = map_x / 8;
    int map_y1 = map_y / 16;

    std::cout << "(" << x << "," << y << ")" << std::endl;
    std::cout << "(" << map_x << "," << map_y << ")" << std::endl;
    std::cout << "(" << map_x1 << "," << map_y1 << ")" << std::endl;


int c=0;


}



int sum(int count, ...) {
    int total = 0;
    
    va_list args;
    va_start(args, count);
    
    for (int i = 0; i < count; i++) {
        int num = va_arg(args, int);
        total += num;
    }
    
    va_end(args);

    int b= 0;
    
    return total;
}

int test_sum() {
    int result = sum(4, 10, 20, 30, 40);
    std::cout << "Sum: " << result << std::endl;
    std::cout << __FUNCTION__ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    
    return 0;
}
