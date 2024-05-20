/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/20 15:31:43 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_pid(void)
{
	pid_t pid;

	pid = getpid();

	printf("%d: command not found\n", pid);
}

void handle_line(t_input *input, t_list_token *data)
{
	t_list_token *curr;
	t_token_type token;

	// Handle Ctrl-D (EOF)
	if (input->line == NULL)
	{
		printf("exit\n");
		exit(1);
	}

	while ((token = check_token(input->line, &data)) != END)
		{
			assign_token_to_list(input->line, token, &data);
			
		}
	curr = data->next;
	while (curr != NULL && curr->word != NULL)
	{
		// printf("words are: %s\n", curr->word);
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
			// else
			// 	printf("Unknown command: %s\n", args[0]);
		}
		curr = curr->next;
	}
}
