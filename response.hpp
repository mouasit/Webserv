#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <sys/stat.h>

typedef struct request{

    std::string method;
    std::string uri;

} request;


typedef struct config{

    std::string root;
    std::string autoindex;
    std::string index[2];

} config;


typedef struct Header{
    std::pair<int,std::string> status;
} Header;

request fill_request(request my_request){
    my_request.method = "GET";
    my_request.uri = "/directory/";
    return my_request;
}

config fill_config()
{
    config config_file;

    config_file.root = ".";
    config_file.index[0] = "index.html";
    config_file.index[1] = "about.html";
    config_file.autoindex = "on";
    return config_file;
}

bool is_directory(const char *uri)
{
    struct stat buff;
    
    lstat(uri,&buff);
    if(S_ISDIR(buff.st_mode))
        return true;
    return false;
}

bool is_slash_in_end(std::string uri, Header &response_header)
{
    /* 
        ------------- TODO -------------
            
            - make a 301 redirection to request uri with '/' addeed at the end.
     */

    if(uri[uri.length() - 1] == '/')
        return true;
    response_header.status.first = 301;
    response_header.status.second = "Moved Permanently";
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

bool is_auto_index(std::string autoIndex, Header &response_header)
{
    if(autoIndex == "on")
        return true;
    response_header.status.first = 403;
    response_header.status.second = "Forbiden";
    return false;
}

#endif