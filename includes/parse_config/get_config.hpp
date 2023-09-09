#ifndef GET_CONFIG_HPP
# define GET_CONFIG_HPP

#include <iostream>
#include <fstream>
#include <sstream>

#include <fcntl.h>
#include <unistd.h>

class Get_config
{
    private:
        std::string path;
        size_t      size;
        int         fd;
        // std::fstream *config;

        Get_config();
        Get_config(Get_config const &oGet_config);
    public:
        Get_config(std::string path);
        ~Get_config();

        // bool returnValidFile() const;
        // bool checkAccess() const;

        std::string getPath() const;
        int getFd() const;

        class InvalidFileException : std::exception
        {
            public:
                virtual const char * what() const throw()
                {
                    return("Invalid file !!!");
                }
        };

        class InvalidFileContentException : std::exception
        {
            public:
                virtual const char* what() const throw()
                {
                    return ("Not in config file format !!!");
                }
        };
};

#endif