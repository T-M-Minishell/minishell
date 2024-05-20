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

//utils

t_list_token	*ft_lstnew(char *content, t_token_type token);
void	ft_lstadd_back(t_list_token **lst, t_list_token *new);
void	free_token_list(t_list_token **stack);
char	*ft_strdnup(const char *s1, int n);
bool	is_space(char *line);

//utils2

t_list_token	*ft_lstnew_init(void);

#endif