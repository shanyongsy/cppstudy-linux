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
