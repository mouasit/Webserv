#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <map>

typedef struct my_request{

    std::string method;
    std::string uri;

} my_request;


typedef struct config{

    std::string root;
    std::string autoindex;
    std::string index[0];

} config;

typedef struct info{
    my_request request;
    config config_file;
} info;

my_request fill_request(my_request request){
    request.method = "GET";
    request.uri = "/directory/";
    return request;
}

config fill_config(config config_file)
{
    config_file.root = ".";
    // config_file.index[0] = "index.html";
    // config_file.index[1] = "about.html";
    config_file.autoindex = "off";
    return config_file;
}

info fill_data(info &data)
{
    data.request = fill_request(data.request);
    data.config_file = fill_config(data.config_file);
    return data;
}


#endif