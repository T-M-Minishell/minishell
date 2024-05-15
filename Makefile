
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = main.c utils.c
LDFLAGS = -lreadline
NAME = minishell
OBJ = $(SRS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cc $(FLAGS) $(SRC) -o $(NAME) $(LDFLAGS)
	rm -rf $(NAME).o

clean:
	rm -f *.o

fclean :clean
	rm -f $(NAME)

re :fclean all

