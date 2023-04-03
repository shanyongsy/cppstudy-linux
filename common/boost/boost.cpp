#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/format.hpp>

#include "struct_def.h"

void example_boost_tokenizer()
{
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    std::string s = "Boost C++ Libraries";
    boost::char_separator<char> sep{" "};
    tokenizer tok{s, sep};
    for (const auto &t : tok)
        std::cout << t << '\n';
}

void example_boost_format()
{
    animal a{"cat", 4};

    auto it = boost::format{"%4% %2% %3% %4% %4%"} % 1 % 2 % 3 % "hello";
    std::cout << it.str() << std::endl;
}

#include <string>
#include <iostream>
#include <sstream>
void example_std_splite()
{
    std::string s = "hello world! welcome to C++";
    std::stringstream ss(s);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, 'l'))
    {
        tokens.push_back(token);
    }

    for (const auto &token : tokens)
    {
        std::cout << token << ", size is " << token.size() << std::endl;
    }
}

#include <boost/algorithm/string.hpp>
#include <set>
void example_boost_splite()
{
    std::string str = "The quick brown fox jumps over the lazy dog";

    {
        std::vector<std::string> words;
        boost::split(words, str, boost::is_any_of(" o"));

        for (const auto &word : words)
        {
            std::cout << word << "-";
        }
        std::cout << std::endl;
    }

    {
        std::set<std::string> words;
        boost::split(words, str, boost::is_any_of(" "));

        for (const auto &word : words)
        {
            std::cout << word << "-";
        }
        std::cout << std::endl;
    }
}
