#include "response.hpp"

int main()
{
    std::vector<Vserver> config_file;
    config_file = parsingConfigFile("file.config");
    response res(config_file[0]._locations);

    if(res.request_valid(res.req, config_file[0]._maxBodySize))
    {
        if(res.check_location_config_file(res.conf.server_location.is_filled,res.conf.server_location._redirection))
        {
            if(res.method_allowed(res.req.method))
            {

            }
        }
    }

    return (0);
}