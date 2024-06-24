/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/24 18:16:38 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_token	*node_creator(t_list_token *data)
{
	t_list_token	*curr;
	t_list_token 	*cmd_node;
	t_redir_cmds 	commands;
	int				length;

	curr = data;
	length = 0;
	commands.arr = NULL;
	commands.next = NULL;
	cmd_node = NULL;
	while (curr != NULL)
	{
		if (curr->type == REDIRECT)
		{
			break;
		}
		length++;
		curr = curr->next;
	}
	curr = data;
	commands.arr = (char **)malloc(siz)
	while (curr != NULL)
	{
		
		curr = curr->next;
	}
	
	return (0);
}

void	handle_redirects(t_list_token *data)
{
	t_list_token	*curr;
	t_list_token	*cmd_node;

	// int fd;
	// int output;
	curr = data;
	cmd_node = node_creator(data);
	// print_node(cmd_node);
	return ;
}

void	handle_tokens_in_prompt(t_list_token *data, char **envp,
		env_var **env_vars)
{
	t_list_token	*curr;

	curr = data;
	(void)envp;
	// printf("%s\n", curr->word);
	if (curr->word != NULL)
	{
		if (strchr(curr->word, '='))
			*env_vars = add_env_var(*env_vars, curr->word);
		if (strcmp(curr->word, "echo") == 0)
			mini_echo(curr, *env_vars);
		if (strcmp(curr->word, "cd") == 0)
			mini_cd(curr);
		if (strcmp(curr->word, "pwd") == 0)
			mini_pwd();
		if (strcmp(curr->word, "exit") == 0)
			mini_exit(curr);
		if (strcmp(curr->word, "export") == 0)
			mini_export(curr, env_vars);
		if (strcmp(curr->word, "unset") == 0)
			*env_vars = mini_unset(curr, *env_vars);
		if (strcmp(curr->word, "env") == 0)
			min_env(curr, *env_vars);
		else
		{
			//			printf("%s\n",curr->word);
			handle_not_existent_builtins(curr, env_vars);
		}
	}
}

void	handle_line(t_input *input, t_list_token *data, char **envp,
		env_var **env_vars)
{
	t_token_type	token;
	char			**arr;
	int				i;
	char			*line_start;

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
		if (token == QUOTE)
		{
			prepare_for_tokenization_quote(arr[i], &data, token);
			free(arr[i]);
		}
		else if (token == WORD)
		{
			prepare_for_tokenization_word(arr[i], &data, token);
			free(arr[i]);
		}
		else if (token == PIPE)
		{
			prepare_for_tokenization_word(arr[i], &data, token);
			free(arr[i]);
		}
		else if (token == REDIRECT)
		{
			prepare_for_tokenization_word(arr[i], &data, token);
			free(arr[i]);
		}
		i++;
	}
	free(arr);
	handle_redirects(data);
	handle_tokens_in_prompt(data, envp, env_vars);
	free_nodes(data);
	// print_node(data);
	// handle_not_existent_builtins(data);
}
