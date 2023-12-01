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
#include <map>

#include <iostream>
#include <random>

#include "func.h"
#include "struct_def.h"
#include "md5c.h"

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
    
    return total;
}

int test_sum() {
    int result = sum(4, 10, 20, 30, 40);
    std::cout << "Sum: " << result << std::endl;
    std::cout << __FUNCTION__ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    
    return 0;
}
