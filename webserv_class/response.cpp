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
        {
            if(location._rootPath[location._rootPath.length() - 1] != '/')
                location._rootPath += "/";
            location._rootPath += (std::string)token;
        }
  	}
	return location._rootPath;
}

void    response::fill_config(Vserver server,Location location)
{
    if(!this->req.uri.length())
        this->req.uri = "/";
    this->conf.root = this->get_root(server._rootPath,location);
    this->conf.autoindex = location._autoindex;
    this->conf.index = location._index;
    this->conf.autoindex = location._autoindex;


}

bool    response::resource_root()
{
    struct stat buff;
	if(lstat(this->conf.root.c_str(),&buff) == -1)
	{
        std::cout << 404 << " " << "Not Found" << std::endl;
		return false;
	}
	return true;
}

bool    response::is_directory()
{
    struct stat buff;
    lstat(this->conf.root.c_str(),&buff);
    if(S_ISDIR(buff.st_mode))
        return true;
    return false;
}

bool    response::is_slash_in_end()
{
    if(this->req.uri[this->req.uri.length() - 1] != '/')
    {
        std::cout << 301 << " " << "Moved Permanently" << std::endl;
        return false;
    }
    return true;
}

bool    response::index_files()
{
    struct stat buff;
    std::string temp = this->conf.root;
    
    if(temp[temp.length() - 1] != '/')
        temp += "/";
	for (size_t i = 0; i < this->conf.index.size(); i++)
	{
		if(lstat((temp + this->conf.index[i]).c_str() ,&buff) == 0)
		{
			this->conf.root = temp + this->conf.index[i];
			return true;
		}
	}
    return false;
}

bool    response::location_has_cgi()
{
    return false;
}

bool    response::is_auto_index()
{
    if(!this->conf.server_location._autoindex.length() || this->conf.server_location._autoindex == "off")
    {
        std::cout << 403 << " " << "Forbidden" << std::endl;
        return false;
    }
    return true;
}

std::string response::get_auto_index_directory()
{
	std::string body;
	std::vector<std::string> list_files;
	std::string links;

	DIR *d;
    struct dirent *dir;

    d = opendir(this->conf.root.c_str());
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
			if(strcmp(dir->d_name,".") != 0 && strcmp(dir->d_name,"..") != 0 && strcmp(dir->d_name,".git") != 0)
			list_files.push_back(dir->d_name);
        }
        closedir(d);
    }

	for (size_t i = 0; i < list_files.size(); i++)
	{
		links+= "    <a href=\"#\">" + list_files[i] + "</a>\n";
	}

	body = "<!DOCTYPE html>\n"\
"<html lang=\"en\">\n"\
"<head>\n"\
"    <meta charset=\"UTF-8\">\n"\
"    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"\
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"\
"    <title>Auto Index</title>\n"\
"    <style>\n"\
"        h1{text-align: center;}\n"\
"    </style>\n"\
"</head>\n"\
"<body>\n"\
+ links + "\n"\
"</body>\n"\
"</html>";

return body;
}


void    response::GET_method(Vserver server, Location location)
{
    this->fill_config(server,location);
    if(resource_root())
    {
        if(is_directory())
        {
            if(is_slash_in_end())
            {
                if(index_files())
                {
                    if(location_has_cgi())
                    {
                        //cgi function.
                    }
                    else
                    {
                        std::cout << this->conf.root << std::endl;
                        std::cout << 200 << " " << "OK" << std::endl;
                    }
                }
                else
                {
                    if(is_auto_index())
                    {
                        std::cout << get_auto_index_directory() << std::endl;
                        std::cout << 200 << " " << "OK" << std::endl;
                    }
                }
            }
        }
        else
        {
            if(location_has_cgi())
            {
                //cgi function.
            }
            else
            {
                std::cout << this->conf.root << std::endl;
                std::cout << 200 << " " << "OK" << std::endl;
            }
        }
    }
}
