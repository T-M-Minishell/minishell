CC = gcc
FLAGS = -Wall -Wextra -Werror -g
#-fsanitize=address
SRC = main.c handle_ctrl_commands.c handle_line_input.c  built_ins.c \
	token_assignation.c utils/utils.c utils/utils2.c un_built_ins.c	\
	handle_env_variables.c  token_preparation.c un_built_ins2.c\
	utils/utils3.c utils/utils4.c custom_split.c execution/handle_pipes.c\
	execution/exec_utils.c execution/handle_builtins_type.c execution/buildins_for_pipe.c\


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
