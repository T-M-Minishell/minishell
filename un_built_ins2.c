/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   un_built_ins2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:37:01 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/24 18:21:39 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void mini_cat(t_list_token *data, env_var *vars) // remake
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
	execute_process("/bin/cat", argv, vars);
	i = 0;
	while (argv[i] != NULL)
		free(argv[i++]);
	free(argv);
}


void mini_touch(t_list_token *data, env_var *vars) // remake
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
	execute_process("/bin/touch", argv, vars);
	i = 0;
	while (argv[i] != NULL)
		free(argv[i++]);
	free(argv);
}

void	mini_mv(t_list_token *data, env_var *vars)
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
	execute_process("/bin/mv", argv, vars);
	i = 0;
	while (argv[i] != NULL)
		free(argv[i++]);
	free(argv);
}


void	mini_wc(t_list_token *data, env_var *vars)
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
	execute_process("/usr/bin/wc", argv, vars);
	i = 0;
	while (argv[i] != NULL)
		free(argv[i++]);
	free(argv);
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
			exit(EXIT_FAILURE);
		}
	} else if (pid < 0) {
		perror("fork");
	} else {
		// Parent process
		wait(&status);
		if (WIFEXITED(status)) {
			vars->exit_status = WEXITSTATUS(status);
		} else {
			vars->exit_status = 2;
		}
	}
}

void mini_expr(t_list_token *data, env_var *vars)
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
		if (strcmp(curr->word, "$?") == 0)
			argv[i++] = ft_itoa(vars->exit_status);
		else
			argv[i++] = strdup(curr->word);
		curr = curr->next;
	}
	argv[i] = NULL;
	execute_process("/usr/bin/expr",argv,vars);
	i = 0;
	while (argv[i] != NULL)
		free(argv[i++]);
	free(argv);
}
