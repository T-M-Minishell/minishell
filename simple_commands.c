/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:37:01 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/10 13:24:19 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_process(char *path, char **argv, t_env_var *vars)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, argv, vars->arr) == -1)
		{
			perror("execve");
			exit(127);
		}
	}
	else if (pid < 0)
		perror("fork");
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			vars->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			vars->exit_status = WTERMSIG(status);
	}
}

int	count_tokens(t_list_token *data)
{
	int				count;
	t_list_token	*curr;

	count = 0;
	curr = data;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

t_env_var	*bultin_check(char **argv, t_env_var *vars)
{
	int	i;

	i = 0;
	if (check_if_builtin(argv[0]))
	{
		vars = handle_tokens_in_prompt(argv, &vars);
		i = 0;
		while (argv[i])
			free(argv[i++]);
		free(argv);
	}
	return (vars);
}

char	**fill_argv(t_list_token *data, char **argv, t_env_var *vars)
{
	int				i;
	t_list_token	*curr;

	curr = data;
	i = 0;
	while (curr != NULL)
	{
		if (strcmp(curr->word, "$?") == 0)
			argv[i++] = ft_itoa(vars->exit_status);
		else
			argv[i++] = strdup(curr->word);
		curr = curr->next;
	}
	argv[i] = NULL;
	return (argv);
}

// t_env_var	*exec_line(t_list_token *data, t_env_var *vars)
// {
// 	int				i;
// 	char			**argv;
// 	char			*path;

// 	i = count_tokens(data);
// 	argv = (char **)malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	argv = fill_argv(data, argv, vars);
// 	vars = bultin_check(argv, vars);
// 	path = get_path(argv[0], vars);
// 	// if (!strcmp(argv[0], "./minishell") || !strcmp(argv[0], "minishell"))
// 	// 	path = (strdup("./minishell"));
// 	if (!path)
// 	{
// 		printf("%s: command not found\n", argv[0]);
// 		free_exec_args(path, argv);
// 		vars->exit_status = 127;
// 		return (vars);
// 	}
// 	execute_process(path, argv, vars);
// 	free_exec_args(path, argv);
// 	return (vars);
// }

t_env_var	*exec_line(t_list_token *data, t_env_var *vars)
{
	int		i;
	char	**argv;
	char	*path;

	i = count_tokens(data);
	argv = (char **)malloc(sizeof(char *) * (i + 1));
	fill_argv(data, argv, vars);
	if (check_if_builtin(argv[0]))
	{
		vars = handle_tokens_in_prompt(argv, &vars);
		i = 0;
		while (argv[i])
			free(argv[i++]);
		free(argv);
		return (vars);
	}
	path = get_path(argv[0], vars);
	if (!strcmp(argv[0], "./minishell") || !strcmp(argv[0], "minishell"))
		path = (strdup("./minishell"));
	if (!path)
	{
		printf("%s: command not found\n", argv[0]);
		free_exec_args(path, argv);
		vars->exit_status = 127;
		return (vars);
	}
	execute_process(path, argv, vars);
	free_exec_args(path, argv);
	return (vars);
}
