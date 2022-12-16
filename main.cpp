#include "response.hpp"

int main(){
    info data;
    Header response_header;

    data = fill_data(data);

    if(data.request.method == "GET")
    {

    }
    if(data.request.method == "POST")
    {
        
    }
    if(data.request.method == "DELETE")
    {
        
    }
    std::cout << response_header.status << std::endl;
}