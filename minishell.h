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
#include <fcntl.h>
#include <dirent.h>


#define MAX_HISTORY 100
#define PROMPT "\033[1m\033[31mminihell*$> \033[0;34m"
#define MAX_PATH 1024
#define BUF_SIZE 1024


typedef struct s_env_var
{
	char **arr;
} env_var;


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
	char		*lines[MAX_HISTORY];
	int			count;
}				t_history;

// utils
t_list_token	*ft_lstnew(char *content, t_token_type token);
void			ft_lstadd_back(t_list_token **lst, t_list_token *new);
void			free_token_list(t_list_token **stack);
char			*ft_strdnup(const char *s1, int n);
bool			is_space(char *line);

// utils2

t_list_token	*ft_lstnew_init(void);
void			ft_lstreset(t_list_token *data, t_token_type token);
int				ft_strlen(const char *str);
char			*ft_strrchr(const char *s, int c);

// utils3
char			*ft_strchr(const char *s, int c);
char			*ft_strdnnup(const char *s1, int n);
void			free_arr(char **arr);
void			ft_lstrest(t_list_token *data, t_token_type token);
char			**ft_split(const char *s, char c);

// utils4

t_list_token	*ft_lstlast(t_list_token *lst);
char			*ft_strdup(const char *s1);
void			print_node(t_list_token *node);

/// handle ctrl_commands
void			ctrl_commands(void);

// handle line_input
void handle_line(t_input *input, t_list_token *data, char **envp, env_var 	**env_vars);

// history
void			create_history(t_history *history, char *line);

// handle env_variable
void	free_vars(env_var *vars);
env_var	*get_env_vars(char** envp);
env_var	*add_env_var(env_var* old_env_vars, char *word);
env_var	*delete_env_var(env_var *old_env_vars, char *key);
char	*get_key_from_word(char *word);
char	*get_value_from_var(char *word, env_var *vars);



			/// built_ins
void	mini_echo(t_list_token *data, env_var *vars);
int		mini_cd(t_list_token *data);
void	mini_pwd(void);
void	mini_exit(t_list_token *data);
void	min_env(t_list_token *data,  env_var 	*env_vars);
env_var	*mini_unset(t_list_token *data, env_var *env_vars);
void	mini_export(t_list_token *data, env_var **env_vars);

// handle_dolar


// token assignation
t_token_type	check_token(char *str);
void			assign_token_to_list(char *line, t_token_type token,
					t_list_token **data);
void			prepare_for_tokenization_quote(char *str, t_list_token **data,
					t_token_type token);
void			prepare_for_tokenization_word(char *str, t_list_token **data,
					t_token_type token);

// ceva /
char			**turn_word_into_arr(t_list_token *data);
void			handle_not_existent_builtins(t_list_token *data, env_var **var);


// un_built_ins2

void	mini_cat(t_list_token *data);
void 	mini_touch(t_list_token *data, env_var *vars);
void 	mini_wc(t_list_token *data, int lines, int words, int chars);
void 	min_mv(t_list_token *data);

// handle_quotes
void			mini_echo_quote(t_list_token *data);

// helper_functions
int ft_strcmp_mod(char *str1, char *str2);
// char	*ft_strdup(char *s1);




#endif