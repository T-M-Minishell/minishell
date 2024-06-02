/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:06:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/22 18:06:51 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool check_if_alphanumeric(char *str)
{
	for (int i = 0; str[i]; i++)
	{
		if (!isalnum((unsigned char)str[i]) && str[i] != '=')
		{
			return false;
		}
	}
	return true;
}

char *get_key_from_word(char *word)
{
	int i = 0;
	while (word[i] != '=')
		i++;
	word[i] = '\0';
	return(word);
}


env_var *get_env_vars(char **envp)
{
	int	i;
	env_var *vars;

	vars = malloc(sizeof(env_var));
	if(!vars)
		return(NULL);
	i = 0;
	while (envp[i])
		i++;
	vars->arr = malloc(sizeof(char *) * (i+1));
	if(!vars->arr)
	{
		free(vars);
		return(NULL);
	}
	i = -1;
	while (envp[++i])
		vars->arr[i] = envp[i];
	vars->arr[i] = NULL;
	return(vars);
}

env_var *add_env_var(env_var *old_env_vars, char *word)
{
	int	i;
	int	j;
	env_var *new_env;

//	if (!check_if_alphanumeric(word))
//		return(NULL);
	new_env = malloc(sizeof(env_var));
	if(!new_env)
		return(NULL);
	i = 0;
	while (old_env_vars->arr[i])
		i++;
	new_env->arr = malloc(sizeof (char *) *(i + 2));
	if(!new_env->arr)
	{
		free(new_env);
		return NULL;
	}
	j = 0;
	while(j < i)
	{
		new_env->arr[j] = strdup(old_env_vars->arr[j]);
		j++;
	}
	free(old_env_vars->arr);
	free(old_env_vars);
	new_env->arr[j] = strdup(word);
	new_env->arr[j+1] = NULL;
	return(new_env);
}

env_var *delete_env_var(env_var *old_env_vars, char *key)
{
	int	i;
	int	j = 0;
	env_var *new_env;

	new_env = malloc(sizeof(env_var));
	if(!new_env)
		return(NULL);
	i = 0;
	while (old_env_vars->arr[i])
		i++;
	new_env->arr = malloc(sizeof (char *) * i);
	if(!new_env->arr)
	{
		free(new_env);
		return NULL;
	}
	i = 0;
	while (old_env_vars->arr[i] != NULL)
	{
		char *copy = strdup(old_env_vars->arr[i]);
		if (strcmp(key, get_key_from_word(copy)) == 0)
		{
			free(copy);
			free(old_env_vars->arr[i]);
			i++;
			continue;
		}
		free(copy);
		new_env->arr[j] = strdup(old_env_vars->arr[i]);
		free(old_env_vars->arr[i]);
		i++;
		j++;
	}
	new_env->arr[j] = NULL;
	free(old_env_vars->arr);
	free(old_env_vars);
	return(new_env);
}
