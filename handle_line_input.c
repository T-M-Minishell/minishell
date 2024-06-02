/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/02 19:08:10 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fcntl.h"
#include "minishell.h"
#include "string.h"

t_list_token	*ft_lstfirst(t_list_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}

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

void	handle_tokens_in_prompt(t_list_token **data, char **envp, t_token_type token)
{
	t_list_token	*curr;
	int				last_exit_status;

	last_exit_status = 0;
	curr = (*data)->next;
	// printf("%s\n", curr->word);
	// printf("%s\n", curr->next->quotes);
	if (curr->word != NULL)
	{
		if ((strcmp(curr->word, "echo") == 0) || (strcmp(curr->quotes, "echo") == 0))
			mini_echo(curr, token);
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
	t_list_token	*tail;

	if (input->line == NULL)
	{
		printf("exit\n");
		exit(1);
	}
	if (input->line[0] == '\0')
		return ;
	arr = ft_split(input->line, ' ');
	if (arr == NULL)
		exit(1);
	i = 0;
	tail = ft_lstlast(data);
	while (arr[i] != NULL)
	{
		token = check_token(arr[i]);
		if (token == QUOTE)
		{
			prepare_for_tokenization_quote(arr[i], &tail, token);
			free(arr[i]);
		}
		else if (token == WORD)
		{
			prepare_for_tokenization_word(arr[i], &tail, token);
			free(arr[i]);
		}
		i++;
	}
	handle_tokens_in_prompt(&data, envp, token);
	ft_lstreset(data, token);
	// if (data->next->quotes != NULL)
	// {
	// 	handle_tokens_in_prompt_for_quotes(data);
	// }
	// handle_not_existent_builtins(data);
}
