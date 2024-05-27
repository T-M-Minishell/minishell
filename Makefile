CC = gcc
FLAGS = -Wall -Wextra -Werror -g
SRC = main.c handle_ctrl_commands.c handle_line_input.c history_functions.c built_ins.c \
	token_assignation.c utils.c utils2.c handle_dolar_sign.c un_built_ins.c	 helper_functions.c \
	create_env_variables.c

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

# run: $(NAME)
# 	./$(NAME)
