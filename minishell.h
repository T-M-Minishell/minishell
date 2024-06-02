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
#include <string.h>

#define MAX_HISTORY 100
#define PROMPT "\033[1m\033[31mminihell*$> \033[0;34m"
#define MAX_PATH 1024

//typedef struct env_var {
//	char *key;
//	char *value;
//	struct env_var *next;
//} env_var;


typedef struct s_env_var
{
	char **arr;
	char* key;
	int 	count;
	char* value;
} env_var;

typedef struct s_dictionary
{
	char key[256];
	char value[256];
	char **dict_arr;
}	t_dictionary;


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
int 	ft_strlen(char *str);

/// handle ctrl_commands
void ctrl_commands();

// handle line_input
void handle_line(t_input *input, t_list_token *data, char **envp, env_var 	**env_vars);

// history
void create_history(t_history *history, char *line);

// handle env_variable
env_var	*get_env_vars(char** envp);
env_var	*add_env_var(env_var* old_env_vars, char *word);
env_var	*delete_env_var(env_var *old_env_vars, char *key);
//env_var	*delete_env_var(env_var *head, char *key);
//env_var	*add_env_var(env_var *head, char *word);
char	*get_key_from_word(char *word);


/// built_ins
void	mini_echo(t_list_token *data);
int		mini_cd(t_list_token *data);
void	mini_pwd(void);
void	mini_exit(void);
void	min_env(t_list_token *data,  env_var 	*env_vars);
env_var *mini_unset(t_list_token *data, env_var *env_vars);
void	mini_export(t_list_token *data);

// handle_dolar
void	handle_dolar(t_list_token *data, int status);

// token assignation
t_token_type check_token(char *str, t_list_token **data);
void assign_token_to_list(char *line, t_token_type token, t_list_token **data);

void print_node(t_list_token *node);

//un_built_ins
char **turn_word_into_arr(t_list_token *data);
void   handle_not_existent_builtins(t_list_token *data);

// helper_functions
int ft_strcmp_mod(char *str1, char *str2);


/// test


#endif