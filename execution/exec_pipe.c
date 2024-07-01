/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:22:42 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/01 17:52:19 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


env_var	*builtin_check_in_pipe(t_list_commands *cmd, env_var *vars)
{
	vars->flag_mod = 0;
	if (check_if_builtin(cmd->arr[0]))
	{
		if (execute_builtins_with_no_output(cmd->arr, vars) == 1)
		{
			vars->flag_mod = 1;
			vars->num_cmds--;
		}
		else if (check_for_env_commands(cmd->arr))
		{
			// vars = exec_env_var_fct(cmd->arr, vars);
			vars->flag_mod = 1;
			vars->num_cmds--;
		}
	}
	return(vars);
}

void child_process(t_list_commands *current, int (*pipes)[2], env_var *vars, int i)
{
	int j;
	char *path;
	
	j = 0;
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < vars->num_cmds - 1)
		dup2(pipes[i][1], STDOUT_FILENO);

	while( j < vars->num_cmds - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	if (check_if_builtin(current->arr[0]))
	{
		if (execute_builtins_with_output(current->arr, vars) == 1)
			_exit(EXIT_SUCCESS);
	}
	else
	{
		path = get_path(current->arr[0],vars);
		if(!path)
		{
			printf("%s: command not found\n", current->arr[0]);
			free(path);
			_exit(127);
		}
		execve(path, current->arr, vars->arr);
		perror("execve");
	}
}


env_var	*parent_process(t_list_commands *current, int pid,int (*pipes)[2], env_var *vars)
{
	int status;
	int i;

	i = vars->index;
	status = 0;
	
	if (i > 0)
		close(pipes[i - 1][0]);
	if (i < vars->num_cmds - 1)
		close(pipes[i][1]);
	if (strcmp(current->arr[0], "cat") != 0)
		waitpid(pid,&status,0);
	if (WIFEXITED(status))
		vars->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		vars->exit_status = WTERMSIG(status);
	return(vars);
}

env_var *execute_commands(t_list_commands *current, int (*pipes)[2], env_var *vars)
{
	int i = 0;
	int pid;
	// int status = 0;
	
	while (i < vars->num_cmds)
	{
		vars = builtin_check_in_pipe(current, vars);
		if(vars->flag_mod == 1)
		{
			current = current->next;
			continue;
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			free(pipes);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)// child process
			child_process(current,pipes,vars,i);
		else
		{ // parent process
			vars->index = i;
			vars = parent_process(current,pid,pipes,vars);
		}
		current = current->next;
		i++;
	}
	return vars;
}
