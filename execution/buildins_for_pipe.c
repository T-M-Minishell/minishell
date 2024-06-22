/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_for_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:48:10 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/22 14:09:07 by msacaliu         ###   ########.fr       */
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

void mini_echo_pipe(char **commands, env_var *vars)
{
    int i = 1;
    int print_new_line = 1;

    if (commands[i] == NULL) {
        ft_putstr("\n");
        return;
    }
    // Check for the -n flag
    while (commands[i] != NULL && commands[i][0] == '-' && commands[i][1] == 'n') {
        if (strcmp(commands[i], "-n-") == 0) break;
        print_new_line = 0;
        i++;
    }
    // Print each argument with a space
    while (commands[i] != NULL) {
        // if (strcmp(commands[i], "|") == 0)
		// 	break;
        if (commands[i][0] == '$')
		{
            char *value = get_value_from_var(commands[i] + 1, vars); // +1 to skip the $
            if (value != NULL)
                ft_putstr(value);
			else
                ft_putstr(" ");
        }
		else
            ft_putstr(commands[i]);
        if (commands[i + 1] != NULL)
            ft_putstr(" ");
        i++;
    }
    // Print new line if -n is not specified
    if (print_new_line)
        ft_putstr("\n");
}

