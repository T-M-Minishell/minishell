/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:35:10 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/23 14:29:34 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


bool check_for_env_commands(char **commands)
{
	if(strcmp(commands[0], "unset") == 0)
		return(true);
	if(strcmp(commands[0], "export") == 0)
		return(true);
	else
		return (false);
}

int	execute_builtins_with_no_output(char **commands)
{
	int flag;

	flag = 0;
	if(strcmp(commands[0], "cd") == 0)
	{
		mini_cd_pipe(commands);
		flag++;
	}
	if(strcmp(commands[0], "exit") == 0)
	{
		mini_exit_pipe(commands);
		flag++;
	}
	return(flag);
}

int	execute_builtins_with_output(char **commands, env_var *vars)
{
	int flag;

	flag = 0;
	if(strcmp(commands[0], "env") == 0)
	{
		mini_env(vars);
		flag = 1;
	}
	else if(strcmp(commands[0], "echo") == 0)
	{
		mini_echo_pipe(commands, vars);
		flag = 1;
	}
	return(flag);
}

env_var *exec_env_var_fct(char **commands, env_var *vars)
{
    env_var *env_vars = vars;

    if (strcmp(commands[0], "unset") == 0)
	{
		env_vars = mini_unset_pipe(commands, vars);
	}
	if (strcmp(commands[0], "export") == 0)
	{
		  env_vars = mini_export_pipe(commands, vars); 
	}
      
    return env_vars;
}