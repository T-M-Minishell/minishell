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
#define MAX_PATH 1024

typedef struct s_input
{
	char *prompt;
	char *line;
	char *direct;
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
void	ft_lstreset(t_list_token *data, t_token_type token);
int 	ft_strlen(const char *str);
char	*ft_strrchr(const char *s, int c);

//utils3
char	*ft_strchr(const char *s, int c);
char	*ft_strdnnup(const char *s1, int n);
void 	free_arr(char **arr);
void	ft_lstrest(t_list_token *data, t_token_type token);
char	**ft_split(const char *s, char c);

/// handle ctrl_commands
void ctrl_commands();

// handle line_input
void handle_line(t_input *input, t_list_token *data, char **envp);

// history
void create_history(t_history *history, char *line);

/// built_ins
void	mini_echo(t_list_token *data);
int		mini_cd(t_list_token *data);
void	mini_pwd(void);
void	mini_exit(void);
void	min_env(t_list_token *data, char **envp);
void	mini_unset(t_list_token *data);

// handle_dolar
void	handle_dolar(t_list_token *data, int status);

// token assignation
t_token_type check_token(char *str, t_list_token *data);
void assign_token_to_list(char *line, t_token_type token, t_list_token **data);

void print_node(t_list_token *node);

//un_built_ins
char **turn_word_into_arr(t_list_token *data);
void   handle_not_existent_builtins(t_list_token *data);

//un_built_ins2

void    mini_cat(char **arr);
void 	mini_touch(char **arr);
void    mini_wc(char **arr);

//handle_quotes
void	mini_echo_quote(t_list_token *data);

#endif