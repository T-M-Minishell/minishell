/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_preparation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:50:41 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/03 15:08:33 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_for_tokenization_quote(char *str, t_list_token **data,
		t_token_type token)
{
	int			start;
	int			end;
	static int	quotes;
	char		*cpy;

	cpy = NULL;
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
			end = (*data)->index - 1;
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

// This function checks for the data type by assigning enum values and returns them back to main
// These "<" || ">" || "|" IF NOT any of these => WORD

void	prepare_for_tokenization_word(char *str, t_list_token **data,
		t_token_type token)
{
	char	*cpy;

	cpy = NULL;
	cpy = ft_strdup(str);
	if (!cpy)
	{
		return ;
	}
	
	assign_token_to_list(cpy, token, &(*data));
	free(cpy);
}

t_token_type check_token(char *str) /// testing
{
	if (strcmp(str, "|") == 0)
		return PIPE;
	// else if (strcmp(str, "<") == 0)
	// 	return REDIRECT_IN;
	// else if (strcmp(str, ">") == 0)
	// 	return REDIRECT_OUT;
	// else if (strcmp(str, ">>") == 0)
	// 	return REDIRECT_APPEND;
	// else if (strcmp(str, "<<") == 0)
	// 	return HEREDOC;
	else if (str[0] == '\'' || str[0] == '"')
		return QUOTE;
	else
		return WORD;
}
