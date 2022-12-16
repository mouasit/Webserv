#include "response.hpp"

int main(){
    info data;
    response_data response_data;

    data = fill_data(data);

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