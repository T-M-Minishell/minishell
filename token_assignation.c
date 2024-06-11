/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assignation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:51:11 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/10 18:35:14 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// debug functions


void	assign_token_to_redirect(char *line, t_list_token **data,
		t_token_type token)
{
	int				start_index;
	char			*str_token;
	t_list_token	*new_node;

	start_index = (*data)->index;
	/// De vazut cum fac cu multiple redirecturi
	while (line[(*data)->index] != '\0')
		(*data)->index++;
	str_token = ft_strdnup(line + start_index, (*data)->index - start_index);
	new_node = ft_lstnew(str_token, token);
	if (new_node == NULL)
	{
		free(str_token);
		free_token_list(data);
		return ;
	}
	new_node->index = (*data)->index;
	ft_lstadd_back(data, new_node);
	// ask sazymon how to handle multiple pipes if anything else shohulkd be skipped here in the end
}

void	assign_token_to_pipe(char *line, t_list_token **data,
		t_token_type token)
{
	int				start_index;
	char			*str_token;
	t_list_token	*new_node;

	start_index = (*data)->index;
	// De vazut cum fac cu multiple pipeuri
	while (line[(*data)->index] != '\0')
		(*data)->index++;
	str_token = ft_strdnup(line + start_index, (*data)->index - start_index);
	new_node = ft_lstnew(str_token, token);
	if (new_node == NULL)
	{
		free(str_token);
		free_token_list(data);
		return ;
	}
	new_node->index = (*data)->index;
	ft_lstadd_back(data, new_node);
	if (line[(*data)->index] != '\0') // Skip the closing quote
		(*data)->index++;
	// ask sazymon how to handle multiple pipes if anything else shohulkd be skipped here in the end
}
void	assign_token_to_word(char *line, t_list_token **data,
		t_token_type token)
{
	t_list_token	*new_node;

	if (line == NULL)
	{
		free_token_list(data);
		return ;
	}
	new_node = ft_lstnew(line, token);
	if (new_node == NULL)
	{
		free_token_list(data);
		return ;
	}
	ft_lstadd_back(data, new_node);
	// free(new_node);
	// print_node((*data)->next);
}

void	assign_token_to_quote(char *line, t_list_token **data,
		t_token_type token)
{
	t_list_token	*new_node;

	if (line == NULL)
	{
		free_token_list(data);
		return ;
	}
	new_node = ft_lstnew(line, token);
	if (new_node == NULL)
	{
		printf("ere\n");
		free_token_list(data);
		return ;
	}
	ft_lstadd_back(data, new_node);
	// free(new_node);
}

//CVb3d2023

// assign to word

// O functie ajutatatuare pt redus de liniim, practic trimite individual,
// bazat pe ce tip de data avem,
// catre o functie care va assignui ce in now catre tipul corespunzator de data

void	assign_token_to_list(char *line, t_token_type token,
		t_list_token **data)
{
	if (token == QUOTE)
		assign_token_to_quote(line, data, token);
	else if (token == WORD)
		assign_token_to_word(line, data, token);
	// else if (token == PIPE)
	// 	assign_toprepre_for_tokenization(arr, &data, token);ken_to_pipe(line,
	// data, token);
	// else if (token == REDIRECT)
	// 	assign_token_to_redirect(line, data, token);
}
