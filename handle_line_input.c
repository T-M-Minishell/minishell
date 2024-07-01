/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/01 12:35:32 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// void	handle_tokens_in_prompt(t_list_token *data,	env_var **env_vars)
// {
// 	t_list_token	*curr;

// 	curr = NULL;
// 	curr = data;

// 	if (curr->word != NULL)
// 	{
// 		// if (strchr(curr->word, '='))
// 		// 	*env_vars = add_env_var(*env_vars, curr->word);
// 		if (strcmp(curr->word, "echo") == 0)
// 			mini_echo(curr, *env_vars);
// 		else if (strcmp(curr->word, "cd") == 0)
// 			mini_cd(curr);
// 		else if (strcmp(curr->word, "pwd") == 0)
// 			mini_pwd();
// 		else if (strcmp(curr->word, "exit") == 0)
// 			mini_exit(curr,(*env_vars)->exit_status);
// 		else if (strcmp(curr->word, "export") == 0)
// 			mini_export(curr, env_vars);
// 		else if (strcmp(curr->word, "unset") == 0)
// 			*env_vars = mini_unset(curr, *env_vars);
// 		else if (strcmp(curr->word, "env") == 0)
// 			mini_env(*env_vars);
// 		else
// 			exec_line(curr,*env_vars);
// 	}
// }

env_var *handle_tokens_in_prompt(char **commands, env_var **env_vars)
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
        // else
        // {
        //     exec_line(commands, *env_vars);
        // }
    }
	return (*env_vars);
}

void	handle_line(t_input *input, t_list_token *data, env_var **env_vars)
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
		if (token == PIPE)
			prepare_for_tokenization_word(arr[i], &data, token);
		if (token == QUOTE)
			prepare_for_tokenization_quote(arr[i], &data, token);
		else if (token == WORD)
			prepare_for_tokenization_word(arr[i], &data, token);
		free(arr[i]);
		i++;
    }
	free(arr);
	if (check_for_pipe_in_line(data))
    	*env_vars = handle_pipe(data, *env_vars);
	else
		*env_vars = exec_line(data, *env_vars);
		// handle_tokens_in_prompt(data,env_vars);
	free_nodes(data);
	// print_node(data);
	// handle_not_existent_builtins(data);
}
