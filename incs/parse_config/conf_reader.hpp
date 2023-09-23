#ifndef CONF_READER_HPP
# define CONF_READER_HPP

#include <iostream>
#include <sstream>
#include <fstream>

class Conf_reader
{
    private:
        std::string path;

    public:
        Conf_reader();
        Conf_reader(std::string path);
        ~Conf_reader();

        bool validate_file() const;
        std::string read_conf() const;

        std::string getPath() const;

        class InvalidFileException : public std::exception
        {
            public:
                virtual const char * what() const throw()
                {
                    return ("Invalid file !!!");
                }
        };
};

#endif