/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:52:15 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/02 15:44:30 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**free_arr_split(char **arr )
{
	int	i;

	i = 0;
	if (arr == NULL)
		return (NULL);
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

int	str_len_mod(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return (i);
}

int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
		{
			trigger = 0;
		}
		str++;
	}
	return (i);
}

char	*create_word(const char *str, int start, char c)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((str_len_mod(&str[start], c) + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (str[start] != c && str[start] != '\0')
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**arr;

	i = 0;
	j = 0;
	arr = malloc ((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !arr)
		return (free_arr_split(arr));
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else if ((s[i] != c))
		{
			arr[j] = create_word(s, i, c);
			if (!arr[j])
				return (free_arr_split(arr));
			j++;
			i = i + str_len_mod(&s[i], c);
		}
	}
	arr[j] = NULL;
	return (arr);
}
char *ft_strjoin(char const *s1, char const *s2)
{
	char *str;
	int i;
	int j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

void free_arr_path(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


char *get_env_path(env_var *env_vars)
{
	int i;
	char *path;

	i = 0;
	while (env_vars->arr[i])
	{
		if(strncmp(env_vars->arr[i], "PATH=",5) == 0)
		{
			path = env_vars->arr[i] + 5;
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char *command, env_var *env_vars)
{
    char *path;
    char **paths;
    char *tmp;
    char *full_path;
    int i;

    path = get_env_path(env_vars);
	if(!path)
		return (NULL);
    paths = ft_split(path, ':');
    i = 0;
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(tmp, command);
		free(tmp);
        if (access(full_path, F_OK) == 0)
        {
            free_arr_path(paths); 
            return full_path; 
        }
        free(full_path);
        i++;
    }
    free_arr_path(paths); 
    return (NULL);
}

