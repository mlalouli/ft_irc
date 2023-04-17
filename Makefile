NAME_P = ircserv

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address 

INC = server.hpp User.hpp Channel.hpp messagerror.hpp

SRC = main.cpp server.cpp User.cpp parsing.cpp Channel.cpp commands.cpp boot.cpp

OBJECTS = $(SRC:.cpp=.o)

all: $(NAME_P)

$(NAME_P): $(OBJECTS)
	@echo "\033[0;32m\n\nCompiling server..."
	@$(CC) -o $(NAME_P) $(OBJECTS)
	@echo "\n\033[0;32mDone."

%.o:%.cpp $(INC)
	@printf "\033[0;33mGenerating server objects... %-10.10s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -f $(OBJECTS) $(OBJECTSB)
	@echo "\n\033[0;31mDeleted.\n"	

fclean: clean
	@rm -f $(NAME_P)

re: fclean all