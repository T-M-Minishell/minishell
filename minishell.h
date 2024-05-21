
#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "parcing.h"
#include <signal.h>
#include <termios.h>
#include "parcing.h"

#define MAX_HISTORY 100
#define PROMPT "\033[31mminihell*$>\033[0;34m"

typedef struct s_input
{
	char *prompt;
	char *line;
	int quote_open;

} t_input;

/// unused for now
typedef struct s_history
{
	char *lines[MAX_HISTORY];
	int count;
} t_history;

// utils

t_list_token	*ft_lstnew(char *content, t_token_type token);
void			ft_lstadd_back(t_list_token **lst, t_list_token *new);
void			free_token_list(t_list_token **stack);
char			*ft_strdnup(const char *s1, int n);
bool			is_space(char *line);


// utils2

t_list_token *ft_lstnew_init(void);

/// handle ctrl_commands
void ctrl_commands();

// handle line_input
void handle_line(t_input *input, t_list_token *data);

// history
void create_history(t_history *history, char *line);

/// built_ins
void	mini_echo(t_list_token *data);
int		mini_cd(t_list_token *data);
void	mini_pwd(void);
void	mini_exit(void);
void	min_env(t_list_token *data);

// handle_dolar
void	handle_dolar(t_list_token *data);

// token assignation
t_token_type check_token(char *str, t_list_token **data);
void assign_token_to_list(char *line, t_token_type token, t_list_token **data);

void print_node(t_list_token *node);

#endif