#include "incs/parse_config/conf_reader.hpp"
#include "incs/parse_config/conf_parser.hpp"

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
            // std::cout << _file << std::endl;

            Conf_parser _parser;
            // _parser.extract_server_blocks(_file);
            _parser.store_server(_file);
            // now we have our servers block stored in block_conf storage //

            return (0);
        }
        std::cerr << "Invalid number of arguments" << std::endl;
        return (1);
    }
    catch(Conf_reader::InvalidFileException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(Conf_parser::OutOfServerBlocks &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(Conf_parser::ErrorEncountered &e)
    {
        std::cerr << e.what() << std::endl;
    }
}