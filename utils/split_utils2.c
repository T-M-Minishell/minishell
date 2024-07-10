/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:59:03 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/10 23:13:24 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_word_quotes(t_dat *indexes, t_word_info *word_info, char *str)
{
	indexes->i++;
	while (str[indexes->i] == '"')
	{
		indexes->i++;
	}
	indexes->is_quotes = !indexes->is_quotes;
	word_info->word[indexes->j] = str[indexes->i];
}

int	allocate_memory(char *str, char c, t_word_info *word_info)
{
	int	alloc;

	alloc = allocate_for_strings(str, c);
	word_info->word = (char *)malloc(sizeof(char) * (alloc + 1));
	return (alloc);
}

// Process string characters
void	process_string(char *str, t_dat *indexes, t_word_info *word_info,
		char c)
{
	int	i;

	i = 0;
	while (str[indexes->i] != '\0' && (indexes->is_quotes
			|| str[indexes->i] != c))
	{
		if (str[indexes->i] == '"' || str[indexes->i] == '\'')
		{
			skip_word_quotes(indexes, word_info, str);
			continue ;
		}
		else if (str[indexes->i + 1] == '|' && !indexes->is_quotes)
		{
			word_info->word[indexes->j++] = str[indexes->i++];
			break ;
		}
		else if (str[indexes->i] == '|' && !indexes->is_quotes)
		{
			word_info->word[indexes->j++] = str[indexes->i++];
			break ;
		}
		else if (str[indexes->i] != '\0' && (indexes->is_quotes
				|| str[indexes->i] != c) && str[indexes->i] != '"')
			word_info->word[indexes->j++] = str[indexes->i++];
	}
}

// Finalize word information
void	finalize_word_info(t_dat *indexes, t_word_info *word_info)
{
	word_info->word[indexes->j] = '\0';
	word_info->char_counted = indexes->i;
}
