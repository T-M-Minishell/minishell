/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:50:53 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/12 13:24:56 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

t_list_token	*ft_lstnew_init(void)
{
	t_list_token	*new;

	new = (t_list_token *)malloc(sizeof(t_list_token));
	if (!new)
		return (NULL);
	new->index = 0;
	new->type = 0;
	new->quotes = NULL;
	new->word = NULL;
	new->pipe = NULL;
	new->redirect = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}


void 	free_nodes(t_list_token *head)
{
	t_list_token *tmp;

	tmp = NULL;
	while (tmp != NULL)
	{
		printf("freed + 1\n");
		tmp = head;
		head = head->next;
		ft_lstreset(tmp, WORD);
		free(tmp);
		tmp = NULL;
	}
}

void	ft_lstreset(t_list_token *data, t_token_type token)
{
	if (data == NULL)
	{
		printf("Data is NULL\n");
		return ;
	}
	if (data->quotes)
	{
		free(data->quotes);
		data->quotes = NULL;
	}
	if (data->word)
	{
		free(data->word);
		data->word = NULL;
	}
	if (data->pipe)
	{
		free(data->pipe);
		data->pipe = NULL;
	}
	data->index = 0;
	data->type = 0;
	data->redirect = NULL;
	if (token == END)
	{
		data->quotes = NULL;
		data->word = NULL;
		data->pipe = NULL;
		data->redirect = NULL;
	}
}

char	**turn_word_into_arr(t_list_token *data)
{
	int				i;
	char			**arr;
	t_list_token	*curr;

	i = 0;
	curr = data->next;
	while (curr != NULL)
	{
		i++;
		curr = curr->next;
	}
	arr = malloc((i + 1) * sizeof(char *));
	if (arr == NULL)
		return (0);
	curr = data;
	i = 0;
	while (curr != NULL)
	{
		arr[i++] = strdup(curr->word);
		curr = curr->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
