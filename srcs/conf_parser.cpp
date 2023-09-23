#include "../incs/parse_config/conf_parser.hpp"
#include "../incs/parse_config/conf_reader.hpp"

Conf_parser::Conf_parser()
{
    this->servers_nbr = 0;
}

Conf_parser::~Conf_parser()
{
}

void Conf_parser::delete_spaces(std::string &_file)
{
    std::string::size_type _start = 0;
    std::string::size_type _end = _file.size() - 1;

    while (_file[_start] && isspace(_file[_start]))
        _start++;
    while (_end != _start && isspace(_file[_end]))
        _end--;
    _file = _file.substr(_start, _end - _start + 1);
}

std::string Conf_parser::first_word(std::string::size_type _start, std::string _file)
{

    int counter = 0;

    // std::string::size_type i = _file.find("server");
    // std::cout << _start << " || " << i << std::endl; 
    // if (i != _start)
    //     throw OutOfServerBlocks();
    // else
    // {
    (void)_start;
    //     i += 6;
    //     return (_file.substr(0, i));
    // }
    // int counter = _start;
    while (isspace(_file[counter]))
        counter++;
    int tmp = counter;
    if (!_file[counter])
        throw OutOfServerBlocks();
    while (_file[counter] && !isspace(_file[counter]))
        counter++;
    return (_file.substr(tmp, counter - tmp));
}
////////////////////////////////////////////

size_t Conf_parser::findStartServer (size_t start, std::string &content)
{
	size_t i;

	for (i = start; content[i]; i++)
	{
		if (content[i] == 's')
			break ;
		if (!isspace(content[i]))
			throw OutOfServerBlocks();
	}
	if (!content[i])
		return (start);
	if (content.compare(i, 6, "server") != 0)
		throw OutOfServerBlocks();
	i += 6;
	while (content[i] && isspace(content[i]))
		i++;
	if (content[i] == '{')
		return (i);
	else
		throw OutOfServerBlocks();

}

/* finding a server end and return the index of } end of server */
size_t Conf_parser::findEndServer (size_t start, std::string &content)
{
	size_t	i;
	size_t	scope;
	
	scope = 0;
	for (i = start + 1; content[i]; i++)
	{
		if (content[i] == '{')
			scope++;
		if (content[i] == '}')
		{
			if (!scope)
				return (i);
			scope--;
		}
	}
	return (start);
}



////////////////////////////////////////////
std::string::size_type Conf_parser::begin_serv(std::string::size_type _start, std::string _file)
{
    std::string::size_type counter = _start;

    // for (counter = 0; _file[counter]; counter++)
    // {
    //     if (first_word(_file) == "server")
    //         break;
    //     if (!isspace(_file[counter]))
    //         throw OutOfServerBlocks();
    // }
    // std::cout << first_word(_start, _file) << "::FALSE" << std::endl;
    if (first_word(_start, _file) != "server")// && !isspace(_file[counter]))
        throw OutOfServerBlocks();
    counter += first_word(_start, _file).size() + 1;
    while (isspace(_file[counter]))
        counter++;
    // std::cout << first_word(_start, _file).size() << std::endl;
    if (_file[counter] != '{')
        throw OutOfServerBlocks();
    // std::cout << "DEBUG11: \n";
    // std::cout << "DEBUG11: ";
    return (counter + 1);
}

std::string::size_type Conf_parser::end_serv(std::string::size_type _start, std::string _file)
{
    std::string::size_type counter;
    int in_block = 0;

    // std::cout << "DEBUG11: " << first_word(_file) << " || DEBUG2: "<< _file.find_first_of("{", 0) << std::endl;
    for (counter = _start + 1; _file[counter]; counter++)
    {
        if (_file[counter] == '{')
            in_block++;
        // std::cout << in_block << std::endl;
        // if (in_block == 0)
            // std::cout << _file[counter - 1] << std::endl;
        if (_file[counter] == '}')
        {
            if (in_block == 0)
                return (counter);
            in_block--;
        }
    }
    // std::cout << "DEBUG11: " << first_word(_file) << std::endl;
    throw OutOfServerBlocks();
}


void Conf_parser::extract_server_blocks(std::string _file)
{
    std::string::size_type _start = 0;
    std::string::size_type _end = _start + 1;

    // (void)_start;
    // (void)_end;

    // std::cout << _file << std::endl;
    delete_spaces(_file);
    if (_file.find("server") == std::string::npos)
        throw Conf_reader::InvalidFileException();
    while (_start != _end && _start < _file.size())
    {
    //     // std::cout << _start << std::endl;
        _start = begin_serv(_start, _file);
        // std::cout << _file << std::endl;
    //     // std::cout << _start << "TE" << std::endl;
    //     // _start = findStartServer(_start, _file);
        _end = end_serv(_start, _file);
    //     // std::cout << "TESTE" << std::endl;
    //     // _end = findEndServer(_start, _file);
    //     // std::cout << "TESTE" << std::endl;
    //     std::cout << _start << " || " << _end << std::endl;
        block_conf.push_back(_file.substr(_start, _end - _start + 1));
    //     _file = _file.substr(_end + 1, _file.size());
    //     // std::cout << _file << " :0HE:\n";
        servers_nbr++;
        _start = _end + 1;

        // return ();
    }
    // std::vector<std::string>::iterator it;
    // for (it = block_conf.begin(); it != block_conf.end(); it++)
    //     std::cout << *(it) << " PRINT " << std::endl;

    // std::cout << servers_nbr << " PRINT " << std::endl;
    // size_t start = 0;
	// size_t end = 1;

	// if (content.find("server", 0) == std::string::npos)
	// 	throw OutOfServerBlocks();
	// while (start != end && start < content.length())
	// {
	// 	start = findStartServer(start, content);
	// 	end = findEndServer(start, content);
	// 	if (start == end)
	// 		throw OutOfServerBlocks();
	// 	this->block_conf.push_back(content.substr(start, end - start + 1));
	// 	this->servers_nbr++;
	// 	start = end + 1;
	// }
}

void Conf_parser::store_server(std::string _file)
{
    extract_server_blocks(_file);
    if (this->servers_nbr != (int)this->block_conf.size())
        throw ErrorEncountered();
    // (void)_file;
    for (int i = 0; i < (int)this->block_conf.size(); i++)
    {
        
    }
}

int Conf_parser::getServers_nbr() const
{
    return (this->servers_nbr);
}