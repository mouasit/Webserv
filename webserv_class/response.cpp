#include "response.hpp"

bool response::request_valid(request req,std::string max_body_size)
{
    if(req.uri.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%") != std::string::npos)
	{
        std::cout << 400 << " " << "Bad Request" << std::endl;
		return false;
	}
	if(req.uri.length() > 2048)
	{
        std::cout << 414 << " " << "Request-URI Too Long" << std::endl;
		return false;
	}
    if(req.body.length() > max_body_size.length())
    {
        std::cout << 413 << " " << "Request Entity Too Large" << std::endl;
        return false;
    }

    return true;
}

Location response::get_location(std::vector<Location> locations)
{
    std::string           temp = this->req.uri;
    std::string           path = "/";
    char                  *token = strtok ((char*)temp.c_str(),"/");
    
    if(token)
        path += (std::string)token;
    for (size_t i = 0; i < locations.size(); i++)
    {
        if(locations[i]._locationPath == path)
        {
            locations[i].is_filled = true;
            return locations[i];
        }
    }
    return Location();
}

bool        response::check_location_config_file(bool is_filled, std::pair<std::string,std::string> redirection)
{
    if(!is_filled)
    {
        std::cout << 404 << " " << "Not Found" << std::endl;
        return false;
    }
    
    if(redirection.first.length())
    {
        std::cout << 301 << " " << "Move Permanently" << std::endl;
        return false;
    }
    return true;
}

bool response::method_allowed(std::string method)
{
    if(method != "GET" && method != "POST" && method != "DELETE")
    {
        std::cout << 405 << " " << "Method Not Allowed" << std::endl;
		return false;
    }
	return true;
}

std::string response::get_root(std::string root, Location location)
{
    std::string temp = this->req.uri;
    char        *token = strtok ((char*)temp.c_str(),"/");

    if(!location._rootPath.length())
    {
        if(!root.length())
            return "";
        if (root[root.length() - 1] != '/')
			root += "/";
        if(token)
            root+= token;
		return root;
    }
    for (;token != NULL;)
    {
        token = strtok (NULL, "/");
        if(token != NULL)
            location._rootPath += "/" + (std::string)token;
  	}
    if(location._rootPath[location._rootPath.length() - 1] != '/')
        location._rootPath += "/";
	return location._rootPath;
}

void    response::fill_config(Vserver server,Location location)
{
    if(!this->req.uri.length())
        this->req.uri = "/";
    this->conf.root = this->get_root(server._rootPath,location);
    this->conf.autoindex = server._autoindex;
}

bool    response::resource_root(std::string root)
{
    struct stat buff;
	if(lstat(root.c_str(),&buff) == -1)
	{
        std::cout << 404 << " " << "Not Found" << std::endl;
		return false;
	}
	return true;
}


void response::GET_method(Vserver server, Location location)
{
    this->fill_config(server,location);
    if(resource_root(this->conf.root))
    {

    }
}
