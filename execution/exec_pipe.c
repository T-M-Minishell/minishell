/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:22:42 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/01 13:49:26 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// env_var	*builtin_check_in_pipe(t_list_commands *cmd, env_var *vars)
// {
// 	if (check_if_builtin(cmd->arr[0]))
// 	{
// 		if (execute_builtins_with_no_output(cmd->arr, vars) == 1)
// 		{
// 			cmd = cmd->next;
// 			vars->num_cmds--;
// 		}
// 		else if (check_for_env_commands(cmd->arr))
// 		{
// 			vars = exec_env_var_fct(cmd->arr, vars);
// 			cmd = cmd->next;
// 			vars->num_cmds--;
// 		}
// 	}
// 	return(vars);
// }


// env_var *execute_commands(t_list_commands *cmd, int (*pipes)[2], env_var *env_vars)
// {
// 	t_list_commands *current = cmd;
// 	int i = 0;
// 	int pid;
// 	int j;
// 	env_var *vars = env_vars;
// 	int status = 0;
// 	int exit_status = 0;

// 	while (i < env_vars->num_cmds) {
// 		// if (check_if_builtin(current->arr[0]))
// 		// {
// 		// 	if (execute_builtins_with_no_output(current->arr, env_vars) == 1)
// 		// 	{
// 		// 		current = current->next;
// 		// 		num_cmds--;
// 		// 		continue;
// 		// 	}
// 		// 	if (check_for_env_commands(current->arr)) {
// 		// 		vars = exec_env_var_fct(current->arr, vars);
// 		// 		current = current->next;
// 		// 		num_cmds--;
// 		// 		continue;
// 		// 	}
// 		// }
// 		// vars = builtin_check_in_pipe(current,vars);
// 		// continue;

// 		pid = fork();
// 		if (pid < 0) {
// 			perror("fork");
// 			free(pipes);
// 			exit(EXIT_FAILURE);
// 		} else if (pid == 0) { // child process
// 			if (i > 0)
// 				dup2(pipes[i - 1][0], STDIN_FILENO);
// 			if (i < env_vars->num_cmds - 1)
// 				dup2(pipes[i][1], STDOUT_FILENO);

// 			for (j = 0; j < env_vars->num_cmds- 1; j++) {
// 				close(pipes[j][0]);
// 				close(pipes[j][1]);
// 			}

// 			if (check_if_builtin(current->arr[0])) {
// 				if (execute_builtins_with_output(current->arr, vars) == 1)
// 					_exit(EXIT_SUCCESS);
// 			} else {
// 				char *path = get_path(current->arr[0],vars);
// 				if(!path)
// 				{
// 					printf("%s: command not found\n", current->arr[0]);
// 					free(path);
// 					_exit(127);
// 				}
// 				execve(path, current->arr, vars->arr);
// 				perror("execve");
				
// 			}
// 		} else { // parent process
// 			if (i > 0)
// 				close(pipes[i - 1][0]);
// 			if (i < env_vars->num_cmds - 1)
// 				close(pipes[i][1]);
// 			if (strcmp(current->arr[0], "cat") != 0)
// 				waitpid(pid,&status,0);
// 			if (WIFEXITED(status)) {
//                 exit_status = WEXITSTATUS(status);
//                 if (exit_status != 0) {
//                     vars->exit_status = exit_status;
//                 }
//             } else if (WIFSIGNALED(status))
//                 vars->exit_status = WTERMSIG(status);
// 		}
// 		current = current->next;
// 		i++;
// 	}
// 	return vars;
// }