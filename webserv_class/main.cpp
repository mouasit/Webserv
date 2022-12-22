#include "response.hpp"

int main()
{
    std::vector<Vserver> config_file;
    config_file = parsingConfigFile("file.config");
    response res(config_file[0]);

    if(res.request_valid(res.req, config_file[0]._maxBodySize))
    {
        if(res.check_location_config_file(res.conf.location.is_filled,res.conf.location._redirection))
        {
            if(res.method_allowed(res.req.method))
            {
                if(res.req.method == "GET")
                {
                    res.GET_method(config_file[0],res.conf.location);
                }
            }
        }
    }

    return (0);
}