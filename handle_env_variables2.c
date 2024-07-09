/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_variables2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:56:35 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/09 18:58:19 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_vars(t_env_var *vars)
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

t_env_var	*add_env_var(t_env_var *old_env_vars, char *word)
{
	int			i;
	int			j;
	t_env_var	*new_env;

	new_env = malloc(sizeof(t_env_var));
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

t_env_var	*delete_env_var(t_env_var *old_env_vars, char *key)
{
	int			i;
	int			j;
	t_env_var	*new_env;
	char		*old_key;

	j = 0;
	new_env = malloc(sizeof(t_env_var));
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
