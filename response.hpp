#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <sys/stat.h>
#include <map>

typedef struct my_request{

    std::string method;
    std::string uri;

} my_request;


typedef struct config{

    std::string root;
    std::string autoindex;
    std::string index[2];

} config;


typedef struct info{
    my_request request;
    config config_file;
} info;


typedef struct Header{
 std::string status;
} Header;

my_request fill_request(my_request request){
    request.method = "GET";
    request.uri = "/directory/";
    return request;
}

config fill_config(config config_file)
{
    config_file.root = ".";
    config_file.index[0] = "index.html";
    config_file.index[1] = "about.html";
    config_file.autoindex = "on";
    return config_file;
}

info fill_data(info &data)
{
    data.request = fill_request(data.request);
    data.config_file = fill_config(data.config_file);
    return data;
}

std::map<int,std::string>   fill_status(std::map<int,std::string> status)
{
    status.insert(std::make_pair(200,"OK"));
    status.insert(std::make_pair(404,"Not Found"));
    status.insert(std::make_pair(301,"Moved Permanently"));
    status.insert(std::make_pair(403,"Forbidden"));
    return status;
}

void set_status(int code, std::string &message, std::map<int,std::string> status)
{
    message = std::to_string(code) + " " + status[code];
}

bool is_directory(const char *uri)
{
    struct stat buff;
    
    lstat(uri,&buff);
    if(S_ISDIR(buff.st_mode))
        return true;
    return false;
}

bool is_slash_in_end(std::string uri, Header &response_header,std::map<int,std::string> status)
{
    /* 
        ------------- TODO -------------
            
            - make a 301 redirection to request uri with '/' addeed at the end.
     */

    if(uri[uri.length() - 1] == '/')
        return true;
    set_status(301,response_header.status,status);
    return false;
}

bool check_index_files(config config_file)
{
        /* 
        ------------- TODO -------------
            
            - check location files in index "if path file not found go to the next file".
     */

    if(sizeof(config_file.index)/sizeof(config_file.index[0]) > 0)
        return true;
    return false;
}

bool location_has_cgi()
{
    return false;
}

bool is_auto_index(std::string autoIndex, Header &response_header, std::map<int,std::string> status)
{
    if(autoIndex == "on")
        return true;
    set_status(403,response_header.status,status);
    return false;
}

void    response_get_method(my_request request,config config_file,std::map<int,std::string> status,Header &response_header)
{   
    if(is_directory((config_file.root + request.uri).c_str()))
        {
            if(is_slash_in_end(request.uri,response_header,status))
            {
                if(check_index_files(config_file))
                {
                    if(location_has_cgi())
                    {
                        // run cgi on requested file with GET request method.
                    }
                    else{
                        set_status(200,response_header.status,status);
                    }
                }
                else{
                    if(is_auto_index(config_file.autoindex,response_header,status))
                    {
                        set_status(200,response_header.status,status);
                    }
                }
            }
        }
        else{
            if(location_has_cgi())
            {
                // run cgi on requested file with GET request method.
            }
            else
            {
                set_status(200,response_header.status,status);
            }
        }
}

#endif