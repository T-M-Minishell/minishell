/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/22 13:57:13 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "fcntl.h"
#include "string.h"


void	handle_tokens_in_prompt(t_list_token *data, char **envp)
{
	t_list_token *curr;
	int last_exit_status = 0;
	if(data->next != NULL)
		curr = data->next;
	else
		curr =data;
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
			mini_unset(curr);
		if (strcmp(curr->word, "env") == 0)
			min_env(curr, envp);
		if (curr->word[0] == '$')
			handle_dolar(curr, last_exit_status);
	}
}


void	handle_line(t_input *input, t_list_token *data, char **envp)
{
	t_token_type	token;
	// Handle Ctrl-D (EOF)
	if (input->line == NULL)
	{
		printf("exit\n");
		exit(1);
	}
	if (input->line[0] == '\0')
		return ;
	while ((token = check_token(input->line, &data)) != END)
		assign_token_to_list(input->line, token, &data);
	handle_tokens_in_prompt(data, envp);
	handle_not_existent_builtins(data);
	ft_lstreset(data, token);
}
