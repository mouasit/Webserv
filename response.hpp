#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <sys/stat.h>
#include <map>
#include "./config_file/parser.hpp"
#include "./utils/data.hpp"
#include "./utils/response_helpers.hpp"

/* ------------------------ GET method ------------------------ */

void    response_get_method(info data, response_data &response_data)
{
    code_status status;
    status = fill_status(status);
    if(!check_redirection(data,response_data,status))
    {
        if(resource_root((data.config_file.root).c_str(),response_data,status))
        {
            if(is_directory((data.config_file.root).c_str()))
            {
            if(is_slash_in_end(data,response_data,status))
            {
                if(check_index_files(data))
                {
                    if(location_has_cgi())
                    {
                        // run cgi on requested file with GET request method.
                    }
                    else{
                        data.pages.page_request = data.config_file.root;
                        set_response(200,response_data,status,data);
                    }
                }
                else{
                    if(is_auto_index(data.config_file.autoindex,response_data,status))
                    {
                        data.pages.string_page_request = get_autoindex_directory(data.config_file.root);
                        set_response(200,response_data,status,data);
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
                std::cout << data.config_file.root << std::endl;
                data.pages.page_request = data.config_file.root;
                set_response(200,response_data,status,data);
            }
        }
    }
    }
}

#endif