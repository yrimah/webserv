#include "incs/parse_config/conf_reader.hpp"
#include "incs/parse_config/conf_parser.hpp"
#include "incs/parse_config/server.hpp"

int main(int argc, char **argv)
{
    try
    {
        if (argc == 1 || argc == 2)
        {
            std::string _path;
            if (argc == 1)
                _path = "configs/default.conf";
            else
                _path = argv[1];

            Conf_reader _config(_path);

            if (!_config.validate_file())
                throw Conf_reader::InvalidFileException();
            std::string _file;

            _file = _config.read_conf();
            if (_file.empty())
                throw Conf_reader::InvalidFileException();
            //Conf_parser _parser;
            server k;
            k.serv.store_server(_file);

            // just for test //---------------------------------------------------------------
            std::vector<Server_storage>::iterator it;
            std::vector<Location_storage>::iterator it2;
            //std::cout<<_parser.getServers().begin()->getHost() <<std::endl;
            // it = _parser.getServers().begin();
            //std::cout << _parser.getServers()[0].getLocations()[2].getLocaCgipath()[0] << std::endl;
            // for (it = _parser.getServers().begin(); it != _parser.getServers().end(); it++)
            // {
                // for (it2 = *it.getLocations().begin(); it2 != *it.getLocations().end(); it2++)
                //     std::cout << (*it2).getLocaCgipath() << std::endl;
            // }
            // now we have our servers stored in 'servers' member of conf_parser class //
            
            k.creat_servers();
            k.bindAnd_ListenServers();
            return (0);
        }
        std::cerr << "Invalid number of arguments" << std::endl;
        return (1);
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    // catch(Conf_reader::InvalidFileException &e)
    // {
    //     std::cerr << e.what() << std::endl;
    // }
    // catch(Conf_parser::OutOfServerBlocks &e)
    // {
    //     std::cerr << e.what() << std::endl;
    // }
    // catch(Conf_parser::ErrorEncountered &e)
    // {
    //     std::cerr << e.what() << std::endl;
    // }
    //opendir()
    // add the catch blocks left : my part + cgi on it //
}