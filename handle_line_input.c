/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/09 19:26:37 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe_and_red(t_list_token *data, t_env_var *vars)
{
	t_list_token	*current;
	t_list_token	*segment_start;
	bool			found_redirect;
	bool			processed_segment;

	current = data;
	segment_start = data;
	found_redirect = false;
	processed_segment = false;
	while (current != NULL)
	{
		if (strcmp(current->word, ">") == 0 || strcmp(current->word, "<") == 0
			|| strcmp(current->word, ">>") == 0
			|| strcmp(current->word, "<<") == 0)
			found_redirect = true;
		if (current->next == NULL || strcmp(current->word, "|") == 0)
		{
			if (found_redirect)
			{
				handle_redirects(segment_start, vars);
				found_redirect = false;
			}
			segment_start = current->next;
		}
		current = current->next;
	}
	current = data;
	segment_start = data;
	while (current != NULL)
	{
		if (current->next != NULL && strcmp(current->word, "|") == 0
			&& !processed_segment)
		{
			vars = handle_pipe(segment_start, vars);
			processed_segment = true;
		}
		current = current->next;
	}
}

t_env_var	*handle_tokens_in_prompt(char **commands, t_env_var **env_vars)
{
	if (commands[0] != NULL)
	{
		if (strcmp(commands[0], "echo") == 0)
			mini_echo(commands, *env_vars);
		else if (strcmp(commands[0], "cd") == 0)
			mini_cd(commands, *env_vars);
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

void	handle_line(t_input *input, t_list_token *data, t_env_var **env_vars)
{
	t_token_type	token;
	char			**arr;
	int				i;
	char			*line_start;

	line_start = input->line;
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
		free(arr[i]);
		i++;
	}
	free(arr);
	if (check_for_pipe_in_line(data) && check_for_redirects_in_line(data))
		handle_pipe_and_red(data, *env_vars);
	else if (check_for_pipe_in_line(data))
		*env_vars = handle_pipe(data, *env_vars);
	else if (check_for_redirects_in_line(data))
		handle_redirects(data, *env_vars);
	else
		*env_vars = exec_line(data, *env_vars);
	free_nodes(data);
}
