/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:23:21 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/05 21:16:32 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	else
		return (NULL);
}

void 	free_arr(char **arr)
{
	int i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
	}
	free(arr);
}

void	ft_lstrest(t_list_token *data, t_token_type token)
{
	data->type = 0;
	data->quotes = NULL;
	data->word = NULL;
	data->pipe = NULL;
	data->redirect = NULL;
	data->input = NULL;
	data->output = NULL;
	data->next = NULL;
	data->prev = NULL;
	if (token == END)
	{
		data->quotes = NULL;
		data->word = NULL;
		data->pipe = NULL;
		data->redirect = NULL;
	}
	data->next = NULL;
	data->prev = NULL;
}
