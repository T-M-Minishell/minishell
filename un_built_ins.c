/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   un_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:22:13 by tlupu             #+#    #+#             */
/*   Updated: 2024/05/22 20:57:11 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_ls(char **arr)
{
	pid_t		pid;
	char		*path;
	extern char	**__environ;

	path = "/bin/ls";
	pid = fork();
	if (pid < 0)
	{
		perror("ERROR WITH PID\n");
		return ;
	}
	else if (pid == 0)
		execve(path, arr, __environ);
	else
		wait(NULL);
}

void	mini_mkdir(char **arr)
{
	pid_t		pid;
	char		*path;
	extern char	**environ;

	path = "/bin/mkdir";
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

void	mini_rm(char **arr)
{
	pid_t		pid;
	char		*path;
	extern char	**environ;

	path = "/bin/rm";
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

void	mini_clean(char **arr)
{
	pid_t		pid;
	char		*path;
	extern char	**environ;

	path = "/bin/clear";
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

void	handle_not_existent_builtins(t_list_token *data)
{
	t_list_token	*curr;
	char			**arr;

	curr = NULL;
	curr = data->next;
	arr = turn_word_into_arr(curr);
	if (arr == NULL)
		return ;
	if (curr->word != NULL)
	{
		if (strcmp(curr->word, "ls") == 0)
			mini_ls(arr);
		if (strcmp(curr->word, "mkdir") == 0)
			mini_mkdir(arr);
		if (strcmp(curr->word, "rm") == 0)
			mini_rm(arr);
		if (strcmp(curr->word, "clear") == 0)
			mini_clean(arr);
		if (strcmp(curr->word, "cat") == 0)
			mini_cat(arr);
		if (strcmp(curr->word, "touch") == 0)
			mini_touch(arr);
		if (strcmp(curr->word, "wc") == 0)
			mini_wc(arr);
		
	}
}
