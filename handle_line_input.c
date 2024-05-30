/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/30 17:01:48 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "minishell.h"
#include "string.h"

void	handle_tokens_in_prompt_for_quotes(t_list_token *data)
{
	t_list_token	*curr;

	// int 			last_exit_status;
	curr = data->next;
	// print_node(curr);
	// print_node(curr->next);
	if (curr->quotes != NULL)
	{
		if (strcmp(curr->quotes, "echo") == 0)
			mini_echo_quote(curr);
	}
}

void	handle_tokens_in_prompt(t_list_token *data, char **envp)
{
	t_list_token	*curr;
	int				last_exit_status;

	last_exit_status = 0;
	curr = data->next;
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
	char			**arr;
	int				i;

	// printf("%s\n", input->line);
	// exit(1);
	// arr = ft_split(input->line,' ');
	// int i = 0;
	// while (arr[i] != NULL)
	// {
	// 	printf("%s\n",arr[i]);
	// 	i++;
	// }
	// Handle Ctrl-D (EOF)
	if (input->line == NULL)
	{
		printf("exit\n");
		exit(1);
	}
	if (input->line[0] == '\0')
		return ;
	i = 0;
	arr = ft_split(input->line, ' ');
	if (arr == NULL)
		exit(1);
	token = check_token(&input->line[i]);
	while (arr[i] != NULL)
	{
		prepre_for_tokenization(arr[i], &data, token);
		// free(arr[i]);
		i++;
		printf("%s\n", arr[i]);
	}
	ft_lstreset(data, token);
	// free_arr(arr);
	// free_arr(arr);
	// if (data->next->quotes != NULL)
	// {
	// 	handle_tokens_in_prompt_for_quotes(data);
	// }
	// handle_not_existent_builtins(data);
	if (token == 100)
	{
		handle_tokens_in_prompt(data, envp);
	}
}
