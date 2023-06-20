#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <string>
#include <fstream>
#include <iconv.h>
#include <malloc.h>

#include "func.h"

bool is_str_gbk(const char* str)
{
    unsigned int nBytes = 0;//GBK可用1-2个字节编码,中文两个 ,英文一个
    unsigned char chr = *str;
    bool bAllAscii = true; //如果全部都是ASCII,
    for (unsigned int i = 0; str[i] != '\0'; ++i) {
        chr = *(str + i);
        if ((chr & 0x80) != 0 && nBytes == 0) {// 判断是否ASCII编码,如果不是,说明有可能是GBK
            bAllAscii = false;
        }
        if (nBytes == 0) {
            if (chr >= 0x80) {
                if (chr >= 0x81 && chr <= 0xFE) {
                    nBytes = +2;
                }
                else {
                    return false;
                }
                nBytes--;
            }
        }
        else {
            if (chr < 0x40 || chr>0xFE) {
                return false;
            }
            nBytes--;
        }//else end
    }
    if (nBytes != 0) {   //违返规则
        return false;
    }
    if (bAllAscii) { //如果全部都是ASCII, 也是GBK
        return true;
    }
    return true;
}

int code_convert(const char* from_charset, const char* to_charset, char* inbuf, size_t inlen,
    char* outbuf, size_t outlen) {
    iconv_t cd;
    char** pin = &inbuf;
    char** pout = &outbuf;

    cd = iconv_open(to_charset, from_charset);
    if (cd == 0)
        return -1;

    memset(outbuf, 0, outlen);

    if ((int)iconv(cd, pin, &inlen, pout, &outlen) == -1)
    {
        iconv_close(cd);
        return -1;
    }
    iconv_close(cd);
    //*pout = '\0';

    return 0;
}

int u2g(char* inbuf, size_t inlen, char* outbuf, size_t outlen) {
    return code_convert("utf-8", "gbk", inbuf, inlen, outbuf, outlen);
}

int g2u(char* inbuf, size_t inlen, char* outbuf, size_t outlen) {
    return code_convert("gbk", "utf-8", inbuf, inlen, outbuf, outlen);
}

void gbk2utf8(const std::string& strGBK, std::string& out)
{
    out.clear();

    if (!is_str_gbk(strGBK.c_str()))
    {
        out = strGBK;
        return;
    }

    int length = strGBK.size() * 3 + 1;
    char* temp = (char*)malloc(sizeof(char) * length);

    if (g2u((char*)strGBK.c_str(), strGBK.size(), temp, length) >= 0)
    {
        out.append(temp);
        free(temp);
    }
    else
    {
        free(temp);
    }
}

void utf82gbk(const char* utf8, std::string& out)
{
    out.clear();

    int length = strlen(utf8);

    char* temp = (char*)malloc(sizeof(char) * length);

    if (u2g((char*)utf8, length, temp, length) >= 0)
    {
        out.append(temp);
        free(temp);

    }
    else
    {
        free(temp);
    }
}

void createDirectory(const std::string& directoryPath) {
    if (mkdir(directoryPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
        std::cerr << "Error creating directory: " << directoryPath << std::endl;
    }
}

void copyFilesWithUTF8(const std::string& sourcePath, const std::string& destinationPath, const std::string& prefix) {
    DIR* dir;
    struct dirent* entry;
    struct stat fileStat;

    dir = opendir(sourcePath.c_str());
    if (dir == nullptr) {
        std::cerr << "Error opening directory: " << sourcePath << std::endl;
        return;
    }

    // 遍历源目录下的所有子目录和文件
    while ((entry = readdir(dir)) != nullptr) {
        std::string entryName = entry->d_name;
        std::string sourceEntryPath = sourcePath + "/" + entryName;

        // 转换文件名为UTF-8编码
        std::string utf8EntryName = "";
        gbk2utf8(entryName, utf8EntryName);
        if (utf8EntryName.empty()) {
            std::cerr << "Error converting file name: " << entryName << std::endl;
            continue;
        }

        std::string destinationEntryPath = destinationPath + "/" + prefix + utf8EntryName;

        // 排除当前目录和父目录
        if (entryName == "." || entryName == "..") {
            continue;
        }

        // 获取文件信息
        if (stat(sourceEntryPath.c_str(), &fileStat) == -1) {
            std::cerr << "Error getting file information: " << sourceEntryPath << std::endl;
            continue;
        }

        // 如果是子目录，递归复制子目录下的文件
        if (S_ISDIR(fileStat.st_mode)) {
            createDirectory(destinationEntryPath);
            copyFilesWithUTF8(sourceEntryPath, destinationEntryPath, prefix);
        } else {
            // 如果是文件，执行拷贝操作
            std::ifstream sourceFile(sourceEntryPath, std::ios::binary);
            std::ofstream destinationFile(destinationEntryPath, std::ios::binary);

            if (!sourceFile) {
                std::cerr << "Error opening source file: " << sourceEntryPath << std::endl;
                continue;
            }

            if (!destinationFile) {
                std::cerr << "Error creating destination file: " << destinationEntryPath << std::endl;
                continue;
            }

            destinationFile << sourceFile.rdbuf();

            sourceFile.close();
            destinationFile.close();
        }

        std::cout << "Copied file: " << sourceEntryPath << " -> " << destinationEntryPath << std::endl;
    }

    closedir(dir);
}

int rename_all_file() {
    std::string sourceDirectory = ".";      // 指定源目录路径

   	time_t long_time;
	time( &long_time ); 
    std::string destinationDirectory = "../rename_";
    destinationDirectory.append(std::to_string(long_time).c_str()); // 指定目标目录路径
    std::string prefix = "";                                  // 指定前缀名

    createDirectory(destinationDirectory);
    copyFilesWithUTF8(sourceDirectory, destinationDirectory, prefix);

    return 0;
}
