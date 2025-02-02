#include <iostream>
#include <string>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{

    fs::path currentDir = fs::current_path();
    std::cout << "Current directory: " << currentDir << std::endl;

    std::string str = "dsad";
    std::string str2 = "qqqq";


    std::cout << str + "qqqq" << std::endl;

}