#include "../includes/parse_config/get_config.hpp"

Get_config::Get_config(std::string path)
{
    this->path = path;
    fd = open(path.c_str(), O_RDONLY);
    if (fd < 0)
        throw InvalidFileException();
}

Get_config::~Get_config()
{
}

// bool Get_config::returnValidFile() const
// {
//     // std::fstream config;
//     *fd = open(path.c_str(), O_RDONLY);
//     if (*fd < 0)
//         // throw InvalidFileException();
//         return (false);
//     // std::cout << "OPENED: DEBUG2" << std::endl;
//     // std::cout << "OPENED: " << fd << std::endl;
//     return (true);
//     // std::fstream _sconf(config);
//     // config << "DONE: DEBUG2" << std::endl;
//     // config.close();
//     // return (config);
// }

std::string Get_config::getPath() const
{
    return (this->path);
}

int Get_config::getFd() const
{
    return (fd);
}