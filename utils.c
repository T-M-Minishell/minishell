/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:50:59 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/02 14:55:56 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_strdnup(const char *s1, int n)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 0;
	while (s1[i] != '\0' && i < n)
	{
		i++;
	}
	s2 = (char *)malloc((i + 1) * sizeof(char));
	if (s2 == NULL)
	{
		return (NULL);
	}
	while (j < i)
	{
		s2[j] = s1[j];
		j++;
	}
	s2[j] = '\0';
	return (s2);
}


void	free_token_list(t_list_token **stack)
{
	t_list_token	*tmp;
	t_list_token	*current;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->next;
		current->type = 0;
        current->index = 0;
        current->word = NULL;
        current->arr = NULL;
        current->input = NULL;
        current->output = NULL;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}


void	ft_lstadd_back(t_list_token **lst, t_list_token *new)
{
	t_list_token	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->prev = last; 
}

t_list_token	*ft_lstnew(char *content, t_token_type token)
{
	t_list_token *new;

	new = (t_list_token *)malloc(sizeof(t_list_token));
	if (!new)
		return (NULL);
	new->index = 0;
	new->type = 0;
	new->quotes = NULL;
	new->word = NULL;
	new->pipe = NULL;
	new->redirect = NULL;
	new->input = NULL;
	new->output = NULL;
	new->next = NULL;
	new->prev = NULL;

	if (token == QUOTE)
	{
		new->quotes = strdup(content);
	}
	else if (token == WORD)
	{
		new->word = strdup(content);
	}
	else if (token == PIPE)
		new->pipe = strdup(content);
	else if (token == REDIRECT)
		new->redirect = strdup(content);
	else
		printf("UNEXPECTED TOKEN TYPE\n");
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

bool 	is_space(char *line)
{
	int i;
	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r' || line[i] == '\v' || line[i] == '\f' || line[i] == '\n')
	{
		i++;
		if (line[i] == '\0')
			return (true);
	}
	return (false);
}
