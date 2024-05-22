/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:50:53 by tlupu             #+#    #+#             */
/*   Updated: 2024/05/22 20:36:23 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	ft_strlen(char *str)
{
	int i;
	i = 0;
	while (str[i] != '\0')
		i++;
	return(i);
}

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
