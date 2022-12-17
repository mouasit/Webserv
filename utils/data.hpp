#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <map>
#include "response_helpers.hpp"


my_request fill_request(my_request request){
    request.method = "GET";
    request.uri = "/index.html";
    return request;
}

config fill_config(config config_file)
{
    config_file.root = ".";
    // config_file.index[0] = "index.html";
    // config_file.index[1] = "about.html";
    config_file.autoindex = "on";
    config_file.path_autoindex = "./";
    return config_file;
}

info fill_data(info &data)
{
    data.request = fill_request(data.request);
    data.config_file = fill_config(data.config_file);
    
    data.pages.page_request = "";
    data.pages.string_page_request = "";
    return data;
}


#endif