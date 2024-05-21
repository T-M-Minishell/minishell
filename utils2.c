/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:50:53 by tlupu             #+#    #+#             */
/*   Updated: 2024/05/21 15:54:48 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_token	*ft_lstnew_init(void)
{
	t_list_token	*new;

	new = (t_list_token *)malloc(sizeof(t_list_token));
	if (!new)
		return (NULL);
	new->index = 0;
	new->type = 0;
	new->arr = NULL;
	new->quotes = NULL;
	new->word = NULL;
	new->pipe = NULL;
	new->redirect = NULL;
	new->input = NULL;
	new->output = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_lstreset(t_list_token *data, t_token_type token)
{
	data->index = 0;
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
