/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_preparation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:50:41 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/04 17:01:24 by tlupu            ###   ########.fr       */
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

    // printf("from handle input:%s\n", str);
	cpy = NULL;
	(*data)->index = 0;
	while (str[(*data)->index] != '\0')
	{
		if (str[(*data)->index] == '"')
		{
            // printf("%c\n",str[(*data)->index] );
			start = (*data)->index + 1;
			quotes++;
			(*data)->index++;
            // printf("%d\n",(*data)->index );
			while (str[(*data)->index] != '"' && str[(*data)->index] != '\0')
			{
                // printf("HERE\n");
				if (str[(*data)->index + 1] == '"')
					quotes++;
				(*data)->index++;
			}
			end = (*data)->index - 1;
            // printf("%c\n", str[end]);
			if (quotes % 2 == 0)
			{
				quotes = 0;
				cpy = ft_strdnup(&str[start], end - start);
                // printf("here:%s\n", cpy);
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
	assign_token_to_list(cpy, token, &(*data));
	free(cpy);
}

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
