#include <iostream>
#include <cstring>

void encrypt(char *str, int len)
{
    for (int i = 0; i < len; i++)
    {
        str[i] += 1;
    }

    // 倒序存储
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void decrypt(char *str, int len)
{
    // 还原顺序
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }

    for (int i = 0; i < len; i++)
    {
        str[i] -= 1;
    }
}

int test_encrypt()
{
    char str[] = "hello, world";
    int len = std::strlen(str);

    std::cout << "original: " << str << std::endl;

    encrypt(str, len);
    std::cout << "encrypted: " << str << std::endl;

    decrypt(str, len);
    std::cout << "decrypted: " << str << std::endl;
}
