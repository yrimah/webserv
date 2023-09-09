#include "includes/parse_config/get_config.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc == 1 || argc == 2)
    {
        try
        {
            std::string configFile_path;

            if (argc == 1)
                configFile_path = "config/default.conf";
            else
                configFile_path = argv[1];

            Get_config oGet_config(configFile_path);

            close(oGet_config.getFd()); // close the config file //
            
            std::cout << "DEBUG: " << oGet_config.getPath() << std::endl;
            std::cout << "DEBUG: " << oGet_config.getFd() << std::endl;

            
        }
        catch(Get_config::InvalidFileException &e)
        {
            std::cout << e.what() << std::endl;
        }

        return (0);
    }
    return (1);
}