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
