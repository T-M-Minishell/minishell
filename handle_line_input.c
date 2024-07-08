/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/05 20:46:01 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

env_var	*handle_tokens_in_prompt(char **commands, env_var **env_vars)
{
	if (commands[0] != NULL)
	{
		if (strcmp(commands[0], "echo") == 0)
			mini_echo(commands, *env_vars);
		else if (strcmp(commands[0], "cd") == 0)
			mini_cd(commands);
		else if (strcmp(commands[0], "pwd") == 0)
			mini_pwd();
		else if (strcmp(commands[0], "exit") == 0)
			mini_exit(commands, (*env_vars)->exit_status);
		else if (strcmp(commands[0], "export") == 0)
			*env_vars = mini_export(commands, env_vars);
		else if (strcmp(commands[0], "unset") == 0)
			*env_vars = mini_unset(commands, *env_vars);
		else if (strcmp(commands[0], "env") == 0)
			mini_env(*env_vars);
	}
	return (*env_vars);
}

void	handle_line(t_input *input, t_list_token *data, env_var **env_vars)
{
	t_token_type token;
	char **arr;
	int i;
	char *line_start;

	line_start = input->line;
	if (input->line == NULL)
	{
		printf("exit\n");
		exit(1);
	}
	if (input->line[0] == '\0')
		return ;
	while (*line_start == ' ')
		line_start++;
	if (*line_start == '\0')
		return ;
	arr = custom_split((char *)(input->line + (line_start - input->line)), ' ');
	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		token = check_token(arr[i]);
		if (token == PIPE)
			prepare_for_tokenization_word(arr[i], &data, token);
		else if (token == QUOTE)
			prepare_for_tokenization_quote(arr[i], &data, token);

		else if (token == WORD)
			prepare_for_tokenization_word(arr[i], &data, token);
		else if (token == PIPE)
			prepare_for_tokenization_word(arr[i], &data, token);
		else if (token == REDIRECT)
			prepare_for_tokenization_word(arr[i], &data, token);
		free(arr[i]);
		i++;
	}
	free(arr);
	if (check_for_pipe_in_line(data))
		*env_vars = handle_pipe(data, *env_vars);
	else if (check_for_redirects_in_line(data))
		handle_redirects(data, *env_vars);
	else
		*env_vars = exec_line(data, *env_vars);
	// handle_tokens_in_prompt(data,env_vars);
	free_nodes(data);
	// print_node(data);
	// handle_not_existent_builtins(data);
}
