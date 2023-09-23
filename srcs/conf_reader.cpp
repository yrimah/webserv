#include "../incs/parse_config/conf_reader.hpp"

Conf_reader::Conf_reader()
{
}

Conf_reader::Conf_reader(std::string path)// : path(path)
{
    this->path = path;
}

Conf_reader::~Conf_reader()
{
}

bool Conf_reader::validate_file() const
{
    std::fstream _conf;

    _conf.open(this->path.c_str(), std::ios::in);
    if (!_conf.is_open())
        return (false);
    _conf.close();
    return (true);
}

std::string Conf_reader::read_conf() const
{
    std::ifstream _conf;
    std::stringstream _strConf;
    // Conf_reader _valid;

    _conf.open(this->path.c_str(), std::ios::in);
    // if (!_conf.is_open())
        // throw InvalidFileException();
    _strConf << _conf.rdbuf();
    _conf.close();
    return (_strConf.str());
    // throw InvalidFileException();
}

std::string Conf_reader::getPath() const
{
    return (this->path);
}