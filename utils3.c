/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:23:21 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/02 15:03:38 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	else
		return (NULL);
}

void 	free_arr(char **arr)
{
	int i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
	}
	free(arr);
}

void	ft_lstrest(t_list_token *data, t_token_type token)
{
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

int	ft_words(char *s, char c)
{
	int	i;
	int	word;
	int	flag;

	i = 0;
	word = 0;
	flag = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (flag == 0 && s[i] != c)
		{
			word++;
			flag = 1;
		}
		if (s[i] == c)
			flag = 0;
		i++;
	}
	return (word);
}

int	ft_wordslength(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return (i);
}

char	*ft_strgen(char *s, char c)
{
	int		i;
	char	*d;

	i = 0;
	d = (char *)malloc(ft_wordslength((char *)s, c) + 1);
	if (d == NULL)
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

int	ft_free(char **ptr, char *str)
{
	int	index;
	int	errorcode;

	index = 0;
	errorcode = 0;
	if (str == NULL)
	{
		while (ptr[index])
		{
			free(ptr[index]);
			index++;
		}
		free(ptr);
		errorcode = 1;
	}
	return (errorcode);
}

char	**ft_split(const char *s, char c)
{
	char	**str;
	int		i;
	int		index;

	i = 0;
	index = 0;
	str = (char **)malloc((ft_words((char *)s, c) + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			str[index] = ft_strgen((char *)(s + i), c);
			if (ft_free(str, str[index]) == 1)
				return (NULL);
			i = i + ft_wordslength((char *)(s + i), c);
			index++;
		}
		else
			i++;
	}
	str[index] = NULL;
	return (str);
}

