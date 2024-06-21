#ifndef MINISHELL_H
# define MINISHELL_H
# include "parcing.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define MAX_HISTORY 100
# define PROMPT "\033[1m\033[31mminihell*$> \033[0;34m"
# define MAX_PATH 1024
# define BUF_SIZE 1024

typedef struct s_env_var
{
	char		**arr;
}				env_var;

typedef struct s_input
{
	char		*prompt;
	char		*line;
	char		*direct;
	int			quote_open;
}				t_input;


typedef struct s_list_commands
{
    char **arr;
    struct s_list_commands *next;
} t_list_commands;

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
void			free_nodes(t_list_token *head);
char			*ft_strrchr(const char *s, int c);
void			free_list(t_list_token *head);

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
void		ft_putstr(char *str);
// void 	free_node_list(t_list_token *data);

/// handle ctrl_commands
void			ctrl_commands(void);

// handle line_input
void			handle_line(t_input *input, t_list_token *data, env_var **env_vars);
void	handle_tokens_in_prompt(t_list_token *data,	env_var **env_vars);


// // history
// void			create_history(t_history *history, char *line);

// handle env_variable
void			free_vars(env_var *vars);
env_var			*get_env_vars(char **envp);
env_var			*add_env_var(env_var *old_env_vars, char *word);
env_var			*delete_env_var(env_var *old_env_vars, char *key);
char			*get_key_from_word(char *word);
char			*get_value_from_var(char *word, env_var *vars);

/// built_ins
void			mini_echo(t_list_token *data, env_var *vars);
int				mini_cd(t_list_token *data);
void			mini_pwd(void);
void			mini_exit(t_list_token *data);
void			mini_env(env_var *env_vars);
env_var			*mini_unset(t_list_token *data, env_var *env_vars);
void			mini_export(t_list_token *data, env_var **env_vars);

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

void			mini_cat(t_list_token *data);
void			mini_touch(t_list_token *data, env_var *vars);
void			mini_wc(t_list_token *data, int lines, int words, int chars);
void			min_mv(t_list_token *data);

// handle_quotes
void			mini_echo_quote(t_list_token *data);

// helper_functions

int				ft_strcmp_mod(char *str1, char *str2);
// char	*ft_strdup(char *s1);

// custom_split.c
char			**custom_split(const char *s, char c);

//execution
bool	check_for_pipe_in_line(t_list_token *data);
void	handle_pipe(t_list_token *data, env_var **env_vars);

// exec_utils
bool check_if_builtin(char *word);

// handle_builtins_type
int execute_builtins_with_no_output(char **commands);
int	execute_builtins_with_output(char **commands, env_var *vars);
env_var *exec_env_var_fct(char **commands, env_var *vars);



// builtins_for_pipes
int		mini_cd_pipe(char **command);
void	mini_exit_pipe(char **command);
env_var	*mini_unset_pipe(char **commands, env_var *env_vars);



#endif