/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/21 22:43:02 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_tokens_in_prompt(t_list_token *data)
{
	t_list_token	*curr;

	curr = data->next; ///boolean val
	
	if (curr->word != NULL)
	{
		if (strcmp(curr->word, "echo") == 0)
			mini_echo(curr);
		if (strcmp(curr->word, "cd") == 0)
			mini_cd(curr);
		if (strcmp(curr->word, "pwd") == 0)
			mini_pwd();
		if (strcmp(curr->word, "exit") == 0)
			mini_exit();
		if (strcmp(curr->word, "export") == 0)
			printf("not done yet\n");
		if (strcmp(curr->word, "unset") == 0)
			printf("not done yet\n");
		if (strcmp(curr->word, "env") == 0)
			min_env(curr);
		if (strcmp(curr->word, "$") == 0)
			handle_dolar(curr);
	}
	return(0);
}

void	handle_line(t_input *input, t_list_token *data)
{
	t_token_type	token;
	int i;
	// Handle Ctrl-D (EOF)
	if (input->line == NULL)
	{
		printf("exit\n");
		exit(1);
	}
	while ((token = check_token(input->line, &data)) != END)
		assign_token_to_list(input->line, token, &data);
	i = handle_tokens_in_prompt(data);
	if (i == 0)
		handle_not_existent_builtins(data);
	ft_lstreset(data, token);
}
