#include "response.hpp"

// read froom fiile


int main(){
    
    std::vector<Vserver> config_file;
    info data;
    response_data response_data;
    code_status status;
    
    config_file = parsingConfigFile("file.config");
    data = fill_data(data,config_file);
    status = fill_status(status);

    if(method_allowed(data.request.method))
    {
        if(data.request.method == "GET")
        {
            response_get_method(data,status,response_data);
        }
        if(data.request.method == "POST")
        {

        }
        if(data.request.method == "DELETE")
        {

        }
    }
    else
        set_response(405,response_data,status);
}