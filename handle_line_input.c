/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/30 14:41:20 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_tokens_in_prompt(t_list_token *data, char **envp, env_var 	*env_vars)
{
	t_list_token	*curr;
	(void)envp;
//	int				last_exit_status;
//
//	last_exit_status = 0;
	curr = data->next;
	if(strchr(curr->word, '='))
		env_vars =  add_env_var(env_vars,curr->word);
//	 int i = 0;
//	 while (env_vars[i].key != NULL)
//	 {
//	 	printf("%s=%s\n", env_vars[i].key, env_vars[i].value);
//	 	i++;
//	 }
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
			mini_export(curr);
		if (strcmp(curr->word, "unset") == 0)
			mini_unset(curr);
		if (strcmp(curr->word, "env") == 0)
			min_env(curr, env_vars);
//		if (curr->word[0] == '$')
//			handle_dolar(curr, last_exit_status);
	}
}

void	handle_line(t_input *input, t_list_token *data, char **envp, env_var 	*env_vars)
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
	while (input->line[0] == ' ')
		input->line++;

	while ((token = check_token(input->line, &data)) != END)
		assign_token_to_list(input->line, token, &data);
	handle_tokens_in_prompt(data, envp, env_vars);
	handle_not_existent_builtins(data);
	ft_lstreset(data, token);
}