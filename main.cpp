#include "response.hpp"

// read froom fiile


int main(){
    
    std::vector<Vserver> config_file;
    info data;
    response_data response_data;

    config_file = parsingConfigFile("file.config");
    data = fill_data(data,config_file);

    if(data.request.method == "GET")
    {
        response_get_method(data,response_data);
    }
    if(data.request.method == "POST")
    {
        
    }
    if(data.request.method == "DELETE")
    {
        
    }
    //std::cout << response_data.start_line.status << std::endl;
}