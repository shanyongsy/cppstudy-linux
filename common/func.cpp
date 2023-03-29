#include <iostream>
#include <csignal>
#include <cstring>
#include <sstream>
#include <vector>

#include "func.h"
#include "struct_def.h"
#include "md5c.h"

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
