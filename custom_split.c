/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:17:27 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/12 14:29:00 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	words_count(const char *str, char c)
{
	int		i;
	int		word;
	bool	is_quote;

	i = 0;
	word = 0;
	is_quote = false;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			is_quote = !is_quote;
			if (is_quote)
				word++;
		}
		else if (!is_quote && ((i == 0 || str[i - 1] == c || str[i] == '|')
				&& str[i] != c))
			word++;
		i++;
	}
	if (is_quote)
	{
		printf("Error: missing quote\n");
		return (-1);
	}
	return (word);
}
char	*string_gen(const char *str, char c)
{
	int		i;
	char	*word;
	bool	is_quote;

	i = 0;
	is_quote = false;
	while (str[i] != '\0' && (is_quote || str[i] != c))
	{
		if (str[i] == '\"')
			is_quote = !is_quote;
		else if (str[i] == '|')
		{
			i++;
			break ;
		}
		i++;
	}
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	strncpy(word, str, i);
	word[i] = '\0';
	return (word);
}

char	**custom_split(const char *str, char c)
{
	int		i;
	int		index_array;
	char	**arr;
	int		word_length;

	i = 0;
	index_array = 0;
	word_length = words_count(str, c);
	arr = (char **)malloc(sizeof(char *) * (word_length + 1));
	if (!arr)
	{
		printf("Allocation has failed\n");
		return (NULL);
	}
	while (index_array < word_length)
	{
		arr[index_array] = string_gen((char *)(str + i), c);
		// printf("arr contents are: %s\n", arr[index_array]);
		i += ft_strlen(arr[index_array]) + 1;
		index_array++;
	}
	arr[word_length] = NULL;
	return (arr);
}
