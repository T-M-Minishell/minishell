/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   un_built_ins2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:37:01 by tlupu             #+#    #+#             */
/*   Updated: 2024/05/22 20:59:43 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    mini_cat(char **arr)

{
	pid_t		pid;
	char		*path;
	extern char	**environ;

	path = "/bin/cat";
	pid = fork();
	if (pid < 0)
	{
		perror("ERROR WITH PID\n");
		return ;
	}
	else if (pid == 0)
		execve(path, arr, environ);
	else
		wait(NULL);
}

void    mini_touch(char **arr)
{
    pid_t		pid;
	char		*path;
	extern char	**environ;

	path = "/bin/touch";
	pid = fork();
	if (pid < 0)
	{
		perror("ERROR WITH PID\n");
		return ;
	}
	else if (pid == 0)
		execve(path, arr, environ);
	else
		wait(NULL);
    
}

void    mini_wc(char **arr)
{
    pid_t		pid;
	char		*path;
	extern char	**environ;

	path = "/bin/wc";
	pid = fork();
	if (pid < 0)
	{
		perror("ERROR WITH PID\n");
		return ;
	}
	else if (pid == 0)
		execve(path, arr, environ);
	else
		wait(NULL);
}
