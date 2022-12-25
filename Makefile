NAME = response

SRC =	main.cpp response.cpp\
		./parseConfigFile/Parser.cpp ./parseConfigFile/Lexer.cpp ./parseConfigFile/Token.cpp \
	   	./parseConfigFile/ServerData.cpp ./parseConfigFile/parseConfigFile.cpp

HEADERS = response.hpp\
		./parseConfigFile/Parser.hpp ./parseConfigFile/Lexer.hpp ./parseConfigFile/Token.hpp \
		./parseConfigFile/Exceptions.hpp ./parseConfigFile/ServerData.hpp \
		./parseConfigFile/parseConfigFile.hpp

all : $(NAME)

$(NAME): $(SRC) $(HEADERS)
	@c++  -Wall -Wextra -Werror -std=c++98 $(SRC) -o $(NAME)
	
clean:
	@rm -rf $(NAME)

fclean:
	@rm -rf $(NAME)

re: fclean all