#include "shader.hpp"
// #include <filesystem>
std::string read_file(const std::string &filepath)
{
    // std::cout << "Current Path: " << std::filesystem::current_path() << std::endl;
    std::string result = "";
    std::string line = "";
    std::ifstream file(filepath.c_str());
    // Reading file line by line is the way to go. otherwise receive shader problems during compilation
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            result += line + "\n"; // This new line is also required!
        }
        file.close();
    }
    return result;
}
