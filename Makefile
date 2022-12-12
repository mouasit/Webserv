NAME = response

SRC =  main.cpp
HEADERS = response.hpp

all : $(NAME)

$(NAME): $(SRC) $(HEADERS)
	@c++  -Wall -Wextra -Werror -std=c++98 $(SRC) -o $(NAME)
	
clean:
	@rm -rf $(NAME)

fclean:
	@rm -rf $(NAME)

re: fclean all