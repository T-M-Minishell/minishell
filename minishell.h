#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include "parcing.h"
#include <signal.h>

t_list_token	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list_token **lst, t_list_token *new);
void	free_token_list(t_list_token **stack);
char	*ft_strdnup(const char *s1, int n);

#endif