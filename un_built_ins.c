/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   un_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:22:13 by tlupu             #+#    #+#             */
/*   Updated: 2024/05/23 12:54:09 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void mini_ls(void)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(".");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			printf("%s\n", dir->d_name);
		closedir(d);
	}
}

void    mini_mkdir(char *str,env_var *vars)
{
	pid_t       pid;
	char        *path;

	char *arr[] = {"/bin/mkdir", str, NULL};

	path = "/bin/mkdir";
	pid = fork();
	if (pid < 0)
	{
		perror("ERROR WITH PID\n");
		return ;
	}
	else if (pid == 0)
		execve(path, arr, vars->arr);
	else
		wait(NULL);
}

void    mini_rm(char *str, env_var *vars) ///
{
	pid_t       pid;
	char        *path;
	char *arr[] = {"/bin/mkdir","-rf", str, NULL};


	path = "/bin/rm";
	pid = fork();
	if (pid < 0)
	{
		perror("ERROR WITH PID\n");
		return ;
	}
	else if (pid == 0)
		execve(path, arr, vars->arr);
	else
		wait(NULL);
}

void    mini_clean(env_var *vars)
{
	pid_t       pid;
	char        *path;

	char *arr[] = {"/bin/clear", NULL};

	path = "/bin/clear";
	pid = fork();
	if (pid < 0)
	{
		perror("ERROR WITH PID\n");
		return ;
	}
	else if (pid == 0)
		execve(path, arr, vars->arr);
	else
		wait(NULL);
}

void    handle_not_existent_builtins(t_list_token *data, env_var **vars)
{
	t_list_token    *curr;
	curr = data;

	if (curr->word != NULL)
	{
		if (strcmp(curr->word, "ls") == 0)
			mini_ls();
		if (strcmp(curr->word, "mkdir") == 0)
			mini_mkdir(curr->next->word,*vars);
		if (strcmp(curr->word, "rm") == 0)
			mini_rm(curr->next->word, *vars);
		if (strcmp(curr->word, "clear") == 0)
			mini_clean(*vars);
		if (strcmp(curr->word, "cat") == 0)
			mini_cat(curr->next->word);
		if (strcmp(curr->word, "touch") == 0)
			mini_touch(curr->next->word, *vars);
		if (strcmp(curr->word, "mv") == 0)
			min_mv(curr->next->word, curr->next->next->word);
//		 if (strcmp(curr->word, "wc") == 0)
//		  mini_wc(arr);

	}
}
