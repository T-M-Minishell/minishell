/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   un_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:22:13 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/24 19:29:47 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void mini_ls(t_list_token *data, env_var *vars)
{
	t_list_token *curr;
	int i;
	char **argv;

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
		argv[i++] = strdup(curr->word);
		curr = curr->next;
	}
	argv[i] = NULL;
	execute_process("/bin/ls", argv, vars);
	i = 0;
	while (argv[i] != NULL)
		free(argv[i++]);
	free(argv);
}

void mini_mkdir(t_list_token *data, env_var *vars)
{
	t_list_token *curr;
	int i;
	char **argv;

	i = 0;
	curr = data;
	while (curr != NULL) {
		i++;
		curr = curr->next;
	}
	argv = (char **) malloc(sizeof(char *) * (i + 1));
	i = 0;
	curr = data;
	while (curr != NULL) {
		argv[i++] = strdup(curr->word);
		curr = curr->next;
	}
	argv[i] = NULL;
	execute_process("/bin/mkdir", argv, vars);
	i = 0;
	while (argv[i] != NULL)
		free(argv[i++]);
	free(argv);
}

void mini_rm(t_list_token *data, env_var *vars)
{
	t_list_token *curr;
	int i;
	char **argv;

	i = 0;
	curr = data;
	while (curr != NULL) {
		i++;
		curr = curr->next;
	}
	argv = (char **) malloc(sizeof(char *) * (i + 1));
	i = 0;
	curr = data;
	while (curr != NULL) {
		argv[i++] = strdup(curr->word);
		curr = curr->next;
	}
	argv[i] = NULL;
	execute_process("/bin/rm", argv, vars);
	i = 0;
	while (argv[i] != NULL)
		free(argv[i++]);
	free(argv);
}

void mini_clean(env_var *vars) /// need to check
{
	pid_t pid;
	char *path;

	char *arr[] = {"/bin/clear", NULL};

	path = "/bin/clear";
	pid = fork();
	if (pid < 0)
	{
		perror("ERROR WITH PID\n");
		return;
	}
	else if (pid == 0)
		execve(path, arr, vars->arr);
	else
		wait(NULL);
}

void handle_not_existent_builtins(t_list_token *data, env_var **vars)
{
	t_list_token *curr;
	curr = data;

	if (curr->word != NULL) {
		if (strcmp(curr->word, "ls") == 0)
			mini_ls(curr, *vars);
		else if (strcmp(curr->word, "mkdir") == 0)
			mini_mkdir(curr, *vars);
		else if (strcmp(curr->word, "rm") == 0)
			mini_rm(curr, *vars);
		else if (strcmp(curr->word, "clear") == 0)
			mini_clean(*vars);
		else if (strcmp(curr->word, "cat") == 0)
			mini_cat(curr, *vars);
		else if (strcmp(curr->word, "touch") == 0)
			mini_touch(curr, *vars); ///
		else if (strcmp(curr->word, "mv") == 0)
			mini_mv(curr, *vars);
		else if (strcmp(curr->word, "wc") == 0)
			mini_wc(curr, *vars);
		else if (strcmp(curr->word, "expr") == 0)
			mini_expr(curr, *vars);

	}
}
