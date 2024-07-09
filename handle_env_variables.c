/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:06:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/09 14:41:50 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_if_alphanumeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!isalnum((unsigned char)str[i]) && str[i] != '=')
			return (false);
		i++;
	}
	return (true);
}

char	*get_value_from_var(char *word, env_var *vars)
{
	int		i;
	char	*key_from_word;

	i = 0;
	while (vars->arr[i])
	{
		key_from_word = get_key_from_word(vars->arr[i]);
		if (strcmp(word, key_from_word) == 0)
		{
			free(key_from_word);
			return (strchr(vars->arr[i], '=') + 1);
		}
		free(key_from_word);
		i++;
	}
	return (NULL);
}

char	*get_key_from_word(char *word)
{
	int		i;
	char	*key;

	i = 0;
	while (word[i] != '=' && word[i] != '\0')
	{
		i++;
	}
	key = malloc(i + 1);
	if (key == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strncpy(key, word, i);
	key[i] = '\0';
	return (key);
}

env_var	*get_env_vars(char **envp)
{
	int		i;
	env_var	*vars;

	vars = malloc(sizeof(env_var));
	if (!vars)
	{
		/** !create 3 additional vars 
		 *  PWD=/home/msacaliu/42_projects/github_repos/minishell
		 *  SHLVL=1
		 *  _=/usr/bin/env
		 * */
		return (NULL);
	}
	i = 0;
	while (envp[i])
		i++;
	vars->arr = malloc(sizeof(char *) * (i+1));
	if (!vars->arr)
	{
		free(vars);
		return (NULL);
	}
	i = -1;
	while (envp[++i])
		vars->arr[i] = strdup(envp[i]);
	vars->arr[i] = NULL;
	vars->exit_status = 0;
	return (vars);
}

bool	check_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (false);
	}
	return (true);
}

void	free_vars(env_var *vars)
{
	int	i;

	i = 0;
	while (vars->arr[i])
	{
		free(vars->arr[i]);
		i++;
	}
	free(vars->arr);
	free(vars);
}

env_var	*add_env_var(env_var *old_env_vars, char *word)
{
	int		i;
	int		j;
	env_var	*new_env;

	new_env = malloc(sizeof(env_var));
	if (!new_env)
		return (NULL);
	i = 0;
	while (old_env_vars->arr[i])
		i++;
	new_env->arr = malloc(sizeof(char *) * (i + 2));
	if (!new_env->arr)
	{
		free(new_env);
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		new_env->arr[j] = old_env_vars->arr[j];
		j++;
	}
	new_env->arr[j] = strdup(word);
	if (!new_env->arr[j])
	{
		free(new_env->arr);
		free(new_env);
		return (NULL);
	}
	new_env->arr[j + 1] = NULL;
	free(old_env_vars->arr);
	free(old_env_vars);
	return (new_env);
}

env_var	*delete_env_var(env_var *old_env_vars, char *key)
{
	int		i;
	int		j;
	env_var	*new_env;
	char	*old_key;

	j = 0;
	new_env = malloc(sizeof(env_var));
	if (!new_env)
		return (NULL);
	i = 0;
	while (old_env_vars->arr[i])
		i++;
	new_env->arr = malloc(sizeof(char *) * i);
	if (!new_env->arr)
	{
		free(new_env);
		return (NULL);
	}
	i = 0;
	while (old_env_vars->arr[i] != NULL)
	{
		old_key = get_key_from_word(old_env_vars->arr[i]);
		if (strcmp(key, old_key) != 0)
		{
			new_env->arr[j] = old_env_vars->arr[i];
			j++;
		}
		else
			free(old_env_vars->arr[i]);
		free(old_key);
		i++;
	}
	new_env->arr[j] = NULL;
	free(old_env_vars->arr);
	free(old_env_vars);
	return (new_env);
}
