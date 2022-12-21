#include "parser.hpp"

void	printVserver(std::vector<Vserver> const &v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << "\n\nserver: ------------------- " << i << " -----------------\n\n";
		
		for (std::set<std::pair<std::string, int> >::iterator j = v[i]._listen.begin(); j != v[i]._listen.end(); ++j)
			std::cout << "Host = " << j->first << "  Port = " << j->second << std::endl;

		std::cout << "Allowd_methods = ";
		for (std::set<std::string>::iterator j = v[i]._allowed_methods.begin(); j != v[i]._allowed_methods.end(); ++j)
			std::cout << *j << " ";
		std::cout << std::endl;
		std::cout << "redirection = " << v[i]._redirection.first << " "<< v[i]._redirection.second << std::endl;
		std::cout << "error_page = " << std::endl;
	}
}

void	exitError(std::string const &err)
{
	std::cerr << err << std::endl;
	exit(EXIT_FAILURE);
}

void	trim(std::string *s)
{
	for (size_t i = 0; i < s->length() && (*s)[i] == '\t'; i++)
		s->erase(s->begin() + i--);
	for (size_t i = s->length(); i >= 0 && (*s)[i] == '\t'; --i)
		s->erase(s->begin() + i++);
}

std::vector<std::string>	split(std::string const &line, char del = ' ')
{
	std::vector<std::string> ret;
	std::stringstream ss(line);
	std::string	tmp;
	while (std::getline(ss, tmp, del))
	{
		trim(&tmp);
		if (tmp == " " || tmp.empty())
			continue;
		ret.push_back(tmp);
	}
	return ret;
}

bool	isEqual(const std::set<std::pair<std::string, int> > &element, int port)
{
	std::set<std::pair<std::string, int> >::iterator it;
	for (it = element.begin(); it != element.end(); ++it)
	{
		if (it->second == port)
			return true;
	}
	return false;
}

void	getPortAndHost(std::vector<std::string> &tokens, bool const &insideLocation, std::vector<Vserver> &_serverConfig, int i_S)
{
	if (tokens.size() != 3)
		exitError("error to many argument near directive: <" + tokens[0] + ">");
	if (!insideLocation)
	{
		if (tokens[1] == "localhost")
		{
			tokens[1].clear();
			tokens[1] = "127.0.0.1";
		}
		int port = atoi(tokens[2].c_str());
		if (port <= 0)
			exitError("error port doesn't match the correct format");
		if (isEqual(_serverConfig[i_S]._listen, port))
			exitError("error port already used");
		_serverConfig[i_S]._listen.insert(std::make_pair(tokens[1], port));
	}
	else
		exitError("error find <"+ tokens[0] + "> inside location block");
}

void	getServerName(std::vector<std::string> &tokens, bool const &insideLocation, std::vector<Vserver> &_serverConfig, int i_S)
{
	if (tokens.size() <= 1)
		exitError("error near direction <" + tokens[0] + ">");
	if (insideLocation)
		exitError("error find <"+ tokens[0] + "> inside location block");
	if (_serverConfig[i_S]._serverNames.empty())
		_serverConfig[i_S]._serverNames.assign(tokens.begin() + 1, tokens.end());
	else
		exitError("error to many sarever_name");
}

void	getErrorPage(std::vector<std::string> &tokens, bool const &insideLocation, std::vector<Vserver> &_serverConfig, int i_S)
{
	if (tokens.size() != 3)
		exitError("error near direction <" + tokens[0] + ">");
	if (insideLocation)
		exitError("error find <" + tokens[0] + "> inside location block");
	else
		_serverConfig[i_S]._errorPage.insert(std::make_pair(tokens[1], tokens[2]));
}

void	getMaxBodySize(std::vector<std::string> &tokens, bool const &insideLocation, std::vector<Vserver> &_serverConfig, int i_S, int i_L)
{
	if (tokens.size() != 2 || !isalnum(tokens[1][0]))
		exitError("error near directive <" + tokens[0] + ">");
	if (insideLocation)
		_serverConfig[i_S]._locations[i_L]._maxBodySize = tokens[1];
	else
		_serverConfig[i_S]._maxBodySize = tokens[1];
}

void	getRoot(std::vector<std::string> &tokens, bool const &insideLocation, std::vector<Vserver> &_serverConfig, int i_S, int i_L)
{
	if (tokens.size() != 2)
		exitError("error near directive <" + tokens[0] + ">");
	if (!insideLocation)
	{
		if (_serverConfig[i_S]._rootPath.empty())
			_serverConfig[i_S]._rootPath = tokens[1];
		else
			exitError("error to many <" + tokens[0] + "> in server block");
	}
	else
	{
		if (_serverConfig[i_S]._locations[i_L]._rootPath.empty())
			_serverConfig[i_S]._locations[i_L]._rootPath = tokens[1];
		else
			exitError("error to many <" + tokens[0] + "> in location block");
	}
}

void	getAllowedMethods(std::vector<std::string> &tokens, bool const &insideLocation, std::vector<Vserver> &_serverConfig, int i_S, int i_L)
{
	if (tokens.size() < 2)
		exitError("error near directive <" + tokens[0] + ">");
	if (!insideLocation)
	{
		if (_serverConfig[i_S]._allowed_methods.empty())
		{
			for (size_t i = 1; i < tokens.size(); i++)
				_serverConfig[i_S]._allowed_methods.insert(tokens[i]);
		}
		else
			exitError("error to many <" + tokens[0] + "> inside server block");
	}
	else
	{
		if (_serverConfig[i_S]._locations[i_L]._allowed_methods.empty())
		{
			for (size_t i = 1; i < tokens.size(); i++)
				_serverConfig[i_S]._locations[i_L]._allowed_methods.insert(tokens[i]);
		}
		else
			exitError("error to many <" + tokens[0] + "> inside location block");
	}
}

void	getIndex(std::vector<std::string> &tokens, bool const &insideLocation, std::vector<Vserver> &_serverConfig, int i_S, int i_L)
{
	if (tokens.size() < 2)
		exitError("error near directive <" + tokens[0] + ">");
	if (!insideLocation)
	{
		if (_serverConfig[i_S]._index.empty())
			_serverConfig[i_S]._index.assign(tokens.begin() + 1, tokens.end());
		else
			exitError("error to many <" + tokens[0] + "> inside server block");
	}
	else
	{
		if (_serverConfig[i_S]._locations[i_L]._index.empty())
			_serverConfig[i_S]._locations[i_L]._index.assign(tokens.begin() + 1, tokens.end());
		else
			exitError("error to many <" + tokens[0] + "> inside location block");
	}
}

void	getAutoIndex(std::vector<std::string> &tokens, bool const &insideLocation, std::vector<Vserver> &_serverConfig, int i_S, int i_L)
{
	if (tokens.size() != 2 || (tokens[1] != "on" && tokens[1] != "off"))
		exitError("error near directive <" + tokens[0] + ">");
	if (!insideLocation)
	{
		if (_serverConfig[i_S]._autoindex.empty())
			_serverConfig[i_S]._autoindex = tokens[1];
		else
			exitError("error to many <" + tokens[0] + "> inside server block");
	}
	else
	{
		if (_serverConfig[i_S]._locations[i_L]._autoindex.empty())
			_serverConfig[i_S]._locations[i_L]._autoindex = tokens[1];
		else
			exitError("error to many <" + tokens[0] + "> inside location block");
	}
}

void	getReturn(std::vector<std::string> &tokens, bool const &insideLocation, std::vector<Vserver> &_serverConfig, int i_S, int i_L)
{
	if (tokens.size() != 3)
		exitError("error near directive <" + tokens[0] + ">");
	if (insideLocation)
	{
		if (!_serverConfig[i_S]._locations[i_L]._redirection.first.empty())
			exitError("error to many <" + tokens[0] + "> inside location block");
		_serverConfig[i_S]._locations[i_L]._redirection.first = tokens[1];
		_serverConfig[i_S]._locations[i_L]._redirection.second = tokens[2];
	}
	else
	{
		if (!_serverConfig[i_S]._redirection.first.empty())
			exitError("error to many <" + tokens[0] + "> inside server block");
		_serverConfig[i_S]._redirection.first = tokens[1];
		_serverConfig[i_S]._redirection.second = tokens[2];
	}
}

void	getCGI(std::vector<std::string> &tokens, bool const &insideLocation, std::vector<Vserver> &_serverConfig, int i_S, int i_L)
{
	if (tokens.size() != 3)
		exitError("error near directive <" + tokens[0] + ">");
	if (insideLocation)
		_serverConfig[i_S]._locations[i_L]._cgi.insert(std::make_pair(tokens[1], tokens[2]));
	else
		exitError("error find <" + tokens[0] + "> inside server block");
}

void	getUploadPath(std::vector<std::string> &tokens, bool const &insideLocation, std::vector<Vserver> &_serverConfig, int i_S, int i_L)
{
	if (tokens.size() != 2)
		exitError("error near directive <" + tokens[0] + ">");
	if (insideLocation)
	{
		if (!_serverConfig[i_S]._locations[i_L]._uploadPath.empty())
			exitError("error to many <" + tokens[0] + "> inside location block");
		_serverConfig[i_S]._locations[i_L]._uploadPath = tokens[1];
	}
	else
		exitError("error find <" + tokens[0] + "> inside server block");
}

std::vector<Vserver>	traitVserver(std::vector<Vserver> const &serverConfig)
{
	std::vector<Vserver>	ret;

	for (size_t i = 0; i < serverConfig.size(); i++)
	{
		for (std::set<std::pair<std::string, int> >::iterator j = serverConfig[i]._listen.begin(); j != serverConfig[i]._listen.end(); ++j)
		{
			ret.push_back(serverConfig[i]);
			ret.back()._host = j->first;
			ret.back()._port = j->second;
		}
	}
	return ret;
}

std::vector<Vserver> parsingConfigFile(std::string const &fileName)
{
	std::ifstream 				configFile(fileName);
	std::vector<Vserver>		_serverConfig;
	std::stack<std::string>		brackets;
	bool						insideServer = false;
	bool						insideLocation = false;
	std::string					line;
	int	index_S = -1, index_L = -1;
	if (configFile)
	{
		while (std::getline(configFile, line))
		{
			if (line.empty())
				continue;
			std::vector<std::string> tokens = split(line);
			if (tokens.size())
			{
				if (tokens[0] == "server" && !insideServer)
				{
					if (!brackets.empty())
						exitError("Syntax Error <" + fileName + ">");
					if (tokens.size() == 2 && tokens[1] == "{")
					{
						insideServer = true;
						brackets.push("{");
						_serverConfig.push_back(Vserver());
						index_S++;
						index_L = -1;
					}
					else
						exitError("Missing '{' near " + tokens[0]);
				}
				else if (insideServer)
				{
					if (!strcmp(tokens[0].c_str(), "listen"))
						getPortAndHost(tokens, insideLocation, _serverConfig, index_S);
					else if (!strcmp(tokens[0].c_str(), "root"))
						getRoot(tokens, insideLocation, _serverConfig, index_S, index_L);
					else if (!strcmp(tokens[0].c_str(), "allowed_methods"))
						getAllowedMethods(tokens, insideLocation, _serverConfig, index_S, index_L);
					else if (!strcmp(tokens[0].c_str(), "server_name"))
						getServerName(tokens, insideLocation, _serverConfig, index_S);
					else if (!strcmp(tokens[0].c_str(), "autoindex"))
						getAutoIndex(tokens, insideLocation, _serverConfig, index_S, index_L);
					else if (!strcmp(tokens[0].c_str(), "index"))
						getIndex(tokens, insideLocation, _serverConfig, index_S, index_L);
					else if (!strcmp(tokens[0].c_str(), "error_page"))
						getErrorPage(tokens, insideLocation, _serverConfig, index_S);
					else if (!strcmp(tokens[0].c_str(), "max_body_size"))
						getMaxBodySize(tokens, insideLocation, _serverConfig, index_S, index_L);
					else if (!strcmp(tokens[0].c_str(), "return"))
						getReturn(tokens, insideLocation, _serverConfig, index_S, index_L);
					else if (!strcmp(tokens[0].c_str(), "cgi"))
						getCGI(tokens, insideLocation, _serverConfig, index_S, index_L);
					else if (!strcmp(tokens[0].c_str(), "upload_path"))
						getUploadPath(tokens, insideLocation, _serverConfig, index_S, index_L);
					else if (!strcmp(tokens[0].c_str(), "location"))
					{
						if (tokens[2] != "[" && tokens.size() != 3)
							exitError("Syntax error in <" + tokens[0] + ">");
						insideLocation = true;
						brackets.push("[");
						index_L++;
						_serverConfig[index_S]._locations.push_back(Location());
						_serverConfig[index_S]._locations[index_L]._locationPath = tokens[1];
					}
					else if (!strcmp(tokens[0].c_str(), "]"))
					{
						if (tokens.size() != 1 || brackets.top() != "[")
							exitError("Syntax error in <" + tokens[0] + ">");
						brackets.pop();
						insideLocation = false;
					}
					else if (!strcmp(tokens[0].c_str(), "}"))
					{
						if (tokens.size() != 1 || brackets.top() != "{")
							exitError("Syntax error in <" + tokens[0] + ">");
						brackets.pop();
						insideServer = false;
					}
					else
						exitError("Syntax error in <" + tokens[0] + ">");
				}
			}
		}
		if (!brackets.empty())
			exitError("Syntax Error in <" + fileName + ">");

		//------------------------------------
		// printVserver(_serverConfig);
		configFile.close();
	}
	else
		exitError("Error\nFile doesn't exist");

	return traitVserver(_serverConfig);
}