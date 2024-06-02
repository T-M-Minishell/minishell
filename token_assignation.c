/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assignation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:51:11 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/02 19:00:21 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// debug functions

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	s2 = (char *)malloc((i + 1) * sizeof(char));
	if (s2 == NULL)
	{
		return (NULL);
	}
	while (j <= i)
	{
		s2[j] = s1[j];
		j++;
	}
	return (s2);
}

void	print_node(t_list_token *node)
{
	if (node == NULL)
	{
		printf("Node is NULL\n");
		return ;
	}
	printf("Node content:\n");
	printf("Index: %d\n", node->index);
	printf("Type: %d\n", node->type);
	printf("Quotes: %s\n", node->quotes ? node->quotes : "(null)");
	printf("Word: %s\n", node->word ? node->word : "(null)");
	printf("Pipe: %s\n", node->pipe ? node->pipe : "(null)");
	printf("Redirect: %s\n", node->redirect ? node->redirect : "(null)");
	printf("Input: %s\n", node->input ? node->input : "(null)");
	printf("Output: %s\n", node->output ? node->output : "(null)");
	// Print other fields as needed
}
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
}

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

void	prepare_for_tokenization_quote(char *str, t_list_token **data,
		t_token_type token)
{
	int			start;
	int			end;
	static int	quotes;
	char		*cpy;

	(*data)->index = 0;
	while (str[(*data)->index] != '\0')
	{
		if (str[(*data)->index] == '"')
		{
			start = (*data)->index + 1;
			quotes++;
			(*data)->index++;
			while (str[(*data)->index] != '"' && str[(*data)->index] != '\0')
			{
				if (str[(*data)->index + 1] == '"')
					quotes++;
				(*data)->index++;
			}
			end = (*data)->index;
			if (quotes % 2 == 0)
			{
				quotes = 0;
				cpy = ft_strdnup(&str[start], end - start);
				assign_token_to_list(cpy, token, &(*data));
				free(cpy);
			}
			(*data)->index++;
		}
		else
			(*data)->index++;
	}
}

void	prepare_for_tokenization_word(char *str, t_list_token **data,
		t_token_type token)
{

	char	*cpy;

	cpy = NULL;
	cpy = ft_strdup(str);
	assign_token_to_list(cpy, token, &(*data));
	free(cpy);
}

// This function checks for the data type by assigning enum values and returns them back to main
// These "<" || ">" || "|" IF NOT any of these => WORD
t_token_type	check_token(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			return (QUOTE);
		else if (str[i] == '|')
			return (PIPE);
		else if (str[i] == '>' || str[i] == '<')
			return (REDIRECT);
		i++;
	}
	return (WORD);
}
