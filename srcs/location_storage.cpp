#include "../incs/parse_config/location_storage.hpp"

Location_storage::Location_storage()
{
}

Location_storage::~Location_storage()
{
}

void Location_storage::init_location()
{
    loca_path = "";
	loca_root = "";
	loca_autoindex = false;
	loca_index = "";
	// loca_return = "";
	loca_alias = "";
	loca_client_max_body_size = 1024; // change it //
	// loca_allowed_methods.reserve(5);
	loca_allowed_methods.push_back(0);
	loca_allowed_methods.push_back(0);
	loca_allowed_methods.push_back(0);
	loca_allowed_methods.push_back(0);
	loca_allowed_methods.push_back(0);
}

// setters //
void Location_storage::setLocaPath(std::string loca_path)
{
    this->loca_path = loca_path;
}

void Location_storage::setLocaRoot(std::string loca_root)
{
	// if (ConfigFile::getTypePath(parametr) != 2)
		// throw ServerConfig::ErrorException("root of location");
    struct stat root_dir;
    int res;

    res = stat(loca_root.c_str(), &root_dir);
    if (root_dir.st_mode & S_IFDIR)
        throw InvalidRootDir();
	this->loca_root = loca_root;
}

void Location_storage::setLocaAllowedMethods(storage allowed_methods)
{
	// this->_methods[0] = 0;
	// this->_methods[1] = 0;
	// this->_methods[2] = 0;
	// this->_methods[3] = 0;
	// this->_methods[4] = 0;

	for (size_t i = 0; i < loca_allowed_methods.size(); i++)
	{
		// if (allowed_methods[i] == "GET")
		// 	this->loca_allowed_methods[0] = 1;
		// else if (allowed_methods[i] == "POST")
		// 	this->loca_allowed_methods[1] = 1;
		// else if (allowed_methods[i] == "DELETE")
		// 	this->loca_allowed_methods[2] = 1;

        switch(allowed_methods[i])
        {
            case "GET":
                this->loca_allowed_methods[0] = 1;
                break;
            case "POST":
                this->loca_allowed_methods[1] = 1;
                break;
            case "DELETE":
                this->loca_allowed_methods[2] = 1;
                break;
            default:
                throw InvalidMethodException();
                // break;
        }
		// else
		// 	throw ServerConfig::ErrorException("Allow method not supported " + methods[i]);
	}
}

void Location_storage::setLocaAutoindex(std::string loca_autoindex)
{
    if (loca_autoindex != "on" && loca_autoindex != "off")
        throw InvalidAutoindex();
    this->loca_autoindex = (loca_autoindex == "on") ? "on" : "off"; 
}

void Location_storage::setLocaIndex(std::string loca_index)
{
	this->loca_index = loca_index;
}

void Location_storage::setLocaAlias(std::string loca_alias)
{
	this->loca_alias = loca_alias;
}

void Location_storage::setLocaCgipath(storage loca_cgi_path)
{
	this->loca_cgi_path = loca_cgi_path;
}

bool Location_storage::check_maxsize(std::string maxsize)
{
    for (int i = 0; i < maxsize.size(); i++)
    {
        if (maxsize[i] > '9' || maxsize[i] < '0')
            throw InvalidMaxSize();
    }
    // if (stoi(maxsize))
    // require more change //
    return (true);
}

void Location_storage::setLoca_client_max_body_size(std::string loca_client_max_body_size)
{
    
}

// getters //
const std::string &Location_storage::getLocaPath() const
{
	return (this->loca_path);
}

const std::string &Location_storage::getLocaRoot() const
{
	return (this->loca_root);
}

const std::vector<int> &Location_storage::getLocaAllowedMethods() const
{
	return (this->loca_allowed_methods);
}

const bool &Location_storage::getLocaAutoindex() const
{
	return (this->loca_autoindex);
}

const std::string &Location_storage::getLocaIndex() const
{
	return (this->loca_index);
}

const std::string &Location_storage::getLocaAlias() const
{
	return (this->loca_alias);
}

const storage &Location_storage::getLocaCgipath() const
{
	return (this->loca_cgi_path);
}

const unsigned long &Location_storage::getLoca_client_max_body_size() const
{
	return (this->loca_client_max_body_size);
}