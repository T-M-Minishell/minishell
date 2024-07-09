CC = gcc
FLAGS = -Wall -Wextra -Werror -g
#-fsanitize=address
SRC = main.c handle_ctrl_commands.c handle_line_input.c  built_ins.c \
	built_ins2.c built_ins3.c handle_env_variables2.c\
	token_assignation.c utils/utils.c utils/utils2.c \
	handle_env_variables.c  token_preparation.c simple_commands.c\
	utils/utils3.c utils/utils4.c custom_split.c execution/handle_pipes.c\
	execution/exec_utils.c execution/handle_builtins_type.c execution/get_path.c\
	execution/exec_pipe.c execution/redirects.c utils/builtin_utils.c



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
