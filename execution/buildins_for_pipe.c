/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_for_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:48:10 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/21 15:14:04 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_cd_pipe(char **command)
{
	
	if (command[1] != NULL)
	{
		if (command[1] == NULL)
		{ // No argument, use HOME directory
			if (chdir(getenv("HOME")) != 0)
			{
				perror("cd");
				return (1);
			}
		}
		else
		{ // Change directory to the provided path
			if (chdir(command[1]) != 0)
			{
				perror("cd");
				return (1);
			}
		}
	}
	return (0);
}

void	mini_exit_pipe(char **command)
{
	int exit_status = 0;

	if (command[1] != NULL)
	{
		exit_status = atoi(command[1]);
	}

	ft_putstr("exit");
	ft_putstr("\n");
	exit(exit_status);
}

env_var	*mini_unset_pipe(char **commands, env_var *env_vars)
{
	int i;

	i = 0;
	if (commands[i] == NULL)
		return (NULL);
	i++;
	if (commands[i] == NULL)
	{
		ft_putstr("unset: requires an argument");
		ft_putstr("\n");
	}
		
	if(strchr(commands[i],'=')!= NULL)
		return env_vars;
	while (commands[i] != NULL)
	{
		env_vars = delete_env_var(env_vars, commands[i]);
		i++;
	}
	return (env_vars);
}
