/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:17:27 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/08 19:41:54 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	words_count(const char *str, char c)
{
	int			i;
	int			word;
	static int	quotes;
	bool		is_quote;
	bool		is_word_started;

	i = 0;
	word = 0;
	quotes = 0;
	is_quote = false;
	is_word_started = false;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			if (!is_quote) // Opening quote
			{
				quotes++; // Increment only for opening quotes
			}
			is_quote = !is_quote; // Toggle is_quote status
			if (is_quote)
			{
				is_word_started = true;
			}
			else
			{
				if (is_word_started)
				{
					word++;
					is_word_started = false;
				}
			}
			i++;
			continue ;
		}
		if (!is_quote)
		{
			if (str[i] == '>' || str[i] == '<')
			{
				if (i > 0 && str[i - 1] == '>')
				{
					word++;
				}
				else if (is_word_started)
				{
					word++;
					is_word_started = false;
				}
				if (str[i] == '>' && str[i + 1] == '>')
				{
					i++;
				}
				word++;
				i++;
				continue ;
			}
			if ((i == 0 || str[i - 1] == c || str[i] == '|') && str[i] != c)
			{
				is_word_started = true;
				if (str[i] == '|' && str[i - 1] != c)
				{
					word++;
				}
			}
			// End current word if encountering separator or pipe
			if (str[i] == c || str[i] == '|')
			{
				if (is_word_started)
				{
					word++;
					is_word_started = false;
				}
				if (str[i] == '|' && str[i + 1] != '\0' && str[i + 1] != c
					&& str[i + 1] != '|')
				{
					is_word_started = true;
				}
			}
		}
		else if (!is_word_started)
		{
			is_word_started = true;
		}
		i++;
	}
	if (is_word_started)
	{
		word++;
	}
	return (word);
}

int	allocate_for_strings(const char *str, char c)
{
	int		i;
	int		l;
	bool	is_quote;

	i = 0;
	l = 0;
	is_quote = false;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			is_quote = !is_quote;
			l++; // Count the quote itself if needed, or remove if not
		}
		else if (!is_quote)
		{
			if (str[i] != c)
			{
				if (str[i] == '>' || str[i] == '<')
				{
					if (str[i] == '>' && str[i + 1] == '>')
					{
						i++;
					}
					l++; // Ensure special characters are counted
				}
				// Adjusted logic: Do not break for pipes; count them if needed
				l++;
			}
		}
		else
		{
			// Inside quotes, count all characters including pipes
			l++;
		}
		i++;
	}
	return (l);
}
// looks for the desired string keeping in mind all the special operators such as "",
t_word_info	string_gen(const char *str, char c)
{
	int			i;
	bool		is_quote;
	int			j;
	int			alloc;
	t_word_info	word_info;

	word_info.word = NULL;
	i = 0;
	j = 0;
	is_quote = false;
	alloc = allocate_for_strings(str, c);
	printf("%d\n", alloc);
	word_info.word = (char *)malloc(sizeof(char) * (alloc + 1));
	if (!word_info.word)
		return (word_info);
	while (str[i] != '\0' && (is_quote || str[i] != c))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i++;
			is_quote = !is_quote;
			if ((is_quote && str[i + 1] != ' ' && str[i + 1] != '\0'))
			{
				word_info.word[j] = str[i];
				continue ;
			}
		}
		else if (str[i + 1] == '|' && !is_quote)
		{
			word_info.word[j++] = str[i];
			i++;
			break ;
		}
		if (str[i] == '|' && !is_quote)
		{
			word_info.word[j++] = str[i++];
			break ;
		}
		if (str[i] != '\0' && (is_quote || str[i] != c) && str[i] != '"')
		{
			word_info.word[j++] = str[i++];
		}
	}
	// printf("j is :%d\n", j);
	word_info.word[j] = '\0';
	word_info.char_counted = i;
	return (word_info);
}

char	**custom_split(const char *str, char c)
{
	int			i;
	int			index_array;
	char		**arr;
	int			word_length;
	t_word_info	word_info;

	i = 0;
	index_array = 0;
	word_length = words_count(str, c);
	// printf("%d\n", word_length);
	// exit(0);
	if (word_length == -1)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (word_length + 1));
	if (!arr)
	{
		printf("Allocation has failed\n");
		return (NULL);
	}
	while (index_array < word_length)
	{
		while (str[i] == c)
			i++;
		word_info = string_gen((char *)(str + i), c);
		arr[index_array] = word_info.word;
		if (word_info.word == NULL)
		{
			break ;
		}
		printf("arr contents are: %s\n", arr[index_array]);
		i += word_info.char_counted;
		index_array++;
	}
	arr[word_length] = NULL;
	return (arr);
}
