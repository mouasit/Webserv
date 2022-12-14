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

} config;


typedef struct Header{
    std::pair<int,std::string> status;
} Header;

request fill_request(request my_request){
    my_request.method = "GET";
    my_request.uri = "/directory";
    return my_request;
}

config fill_config()
{
    config config_file;

    config_file.root = ".";
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

#endif