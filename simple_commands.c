/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:37:01 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/26 17:36:02 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec_args(char *path, char **argv)
{
	int i;
	
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
	free (path);
}

void	execute_process(char *path, char **argv, env_var *vars)
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0) {
		// Child process
		if (execve(path, argv, vars->arr) == -1) {
			perror("execve");
			// if(!path)
			// 	free_exec_args(path, argv);
			exit(127);
		}
	}
	else if (pid < 0)
		perror("fork");
	else
	{// Parent process
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			vars->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			vars->exit_status = WTERMSIG(status);
	}
}

void exec_line(t_list_token *data, env_var *vars)
{
    t_list_token *curr;
    int i;
    char **argv;
    char *path;

    i = 0;
    curr = data;
    while (curr != NULL)
	{
        i++;
        curr = curr->next;
    }
    argv = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    curr = data;
    while (curr != NULL)
	{
        if (strcmp(curr->word, "$?") == 0)
            argv[i++] = ft_itoa(vars->exit_status); 
        else 
            argv[i++] = strdup(curr->word); 
        curr = curr->next;
    }
    argv[i] = NULL;
    path = get_path(argv[0], vars);
    if (!path)
	{
        printf("%s: command not found\n", argv[0]);
		free_exec_args(path,argv);
		vars->exit_status = 127;
		return ;
    }
    execute_process(path, argv, vars);
  	free_exec_args(path,argv);
	return;
}


