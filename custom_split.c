/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:17:27 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/03 17:29:18 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdbool.h>

int words_count(const char *str) {
	int word = 0;
	bool in_quotes = false;
	bool in_word = false;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '\"') {
			in_quotes = !in_quotes; // Toggle in_quotes status
			in_word = true; // We are inside a word because of the quote
		} else if (!in_quotes && str[i] == ' ') {
			if (in_word) {
				// We were in a word, but found a space outside quotes, so increment word count
				word++;
				in_word = false; // Reset in_word status
			}
		} else {
			// Any other character means we are inside a word
			in_word = true;
		}
	}

	// If we end while still in a word, count it
	if (in_word) {
		word++;
	}

	return word;
}

int main() {
	const char *command = "echo hey\"gman\"ero";
	printf("Word count: %d\n", words_count(command));
	return 0;
}
int	allocate_for_strings(const char *str, char c)
{
	int		i;
	int		keep_quotes;
	bool	is_quote;

	i = 0;
	keep_quotes = 0;
	is_quote = false;
	while (str[i] != '\0' && (is_quote || str[i] != c))
	{
		if (str[i] == '\"')
		{
			keep_quotes++;
			is_quote = !is_quote;
			i++;
			continue ;
		}
		else if (str[i] == '|')
		{
			i++;
			break ;
		}
		else if (str[i] == '>' || str[i] == '<')
		{
			i++;
			break ;
		}
		i++;
	}
	if (keep_quotes % 2 == 0)
	{
		i = i - keep_quotes;
	}
	return (i);
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
	alloc = 0;
	alloc = allocate_for_strings(str, c);
	word_info.word = (char *)malloc(sizeof(char) * (alloc + 1));
	if (!word_info.word)
		return (word_info);
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			is_quote = !is_quote;
			i++;
			continue ;
		}
		if (!is_quote && str[i] == c)
		{
			break;
		}
		else if (str[i] == '|')
		{
			word_info.word[j++] = str[i++];
			break ;
		}
		word_info.word[j++] = str[i++];
	}
	printf("%s is :\n", word_info.word);
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
	printf("word_length is: %d\n", word_length);
	exit(0);
	if (word_length == -1)
	{
		return (NULL);
	}
	arr = (char **)malloc(sizeof(char *) * (word_length + 1));
	if (!arr)
	{
		printf("Allocation has failed\n");
		return (NULL);
	}
	while (index_array < word_length)
	{
		word_info = string_gen((char *)(str + i), c);
		arr[index_array] = word_info.word;
		printf("arr contents are: %s\n", arr[index_array]);
		i += word_info.char_counted;
		while (str[i] == c)
			i++;
		index_array++;
	}
	arr[word_length] = NULL;
	return (arr);
}
