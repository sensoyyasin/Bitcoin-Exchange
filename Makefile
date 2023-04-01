NAME = btc
CC = c++
CLAFGS = -Wall -Wextra -Werror -std=c++98
SRCS = $(wildcard *.cpp)
OBJ = $(SRCS:.cpp = .o)

$(NAME): $(OBJ)
	@$(CC) $(CLAFGS) $(SRCS) -o $(NAME)
	@echo "\033[1;92mCompiled succesfully..\033[0m"

all: $(NAME)

clean:
	rm -rf  $(NAME)

fclean: clean


re: fclean all

.PHONY: all clean fclean re