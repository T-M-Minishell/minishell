/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/16 17:40:10 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void handle_pipe(char *line, env_var **env_vars)
{
    
}

void	handle_tokens_in_prompt(t_list_token *data, char **envp,
		env_var **env_vars)
{
	t_list_token	*curr;

	curr = NULL;
	curr = data;
	(void)envp;
	printf("%s\n", curr->word);
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
			handle_not_existent_builtins(curr, env_vars);
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
	arr = custom_split(input->line, ' ');
	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		token = check_token(arr[i]);
		if (token == PIPE)
		{
			handle_pipe(input->line, envp);
			free_arr(arr);
			return;
		}
		if (token == QUOTE)
		{
			prepare_for_tokenization_quote(arr[i], &data, token);
		}
		else if (token == WORD || token == PIPE)
		{
			prepare_for_tokenization_word(arr[i], &data, token);
		}
		free(arr[i]);
		i++;
    }
	free(arr);
	handle_tokens_in_prompt(data, envp, env_vars);
	free_nodes(data);
	// print_node(data);
	// handle_not_existent_builtins(data);
}
