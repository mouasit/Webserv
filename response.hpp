#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <sys/stat.h>
#include <map>
#include "./utils/data.hpp"
#include "./utils/response_helpers.hpp"

/* ------------------------ GET method ------------------------ */

void    response_get_method(info data, response_data &response_data)
{
    code_status status;
    
    status = fill_status(status);
    if(is_directory((data.config_file.root + data.request.uri).c_str()))
        {
            if(is_slash_in_end(data.request.uri,response_data,status))
            {

                if(check_index_files(data.config_file))
                {
                    if(location_has_cgi())
                    {
                        // run cgi on requested file with GET request method.
                    }
                    else{
                        // get index file from indexs in config_file.
                        set_response(200,response_data,status,data.config_file.root + data.request.uri);
                    }
                }
                else{
                    if(is_auto_index(data.config_file.autoindex,response_data,status))
                    {
                        set_response(200,response_data,status,data.config_file.root + data.config_file.path_autoindex);
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
                set_response(200,response_data,status,data.config_file.root + data.request.uri);
            }
        }
}

#endif