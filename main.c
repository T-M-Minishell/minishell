/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:37:18 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/21 18:43:22 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_input input;
	t_list_token *data;
	(void)argv;

	input.prompt = PROMPT;
	data = ft_lstnew_init();
	if (argc != 1)
	{
		printf("args are not allowed\n");
		exit(1);
	}
	while (1)
	{
		// Set up the signal handler for Ctrl+C and CTRL-"\"
		ctrl_commands();
		// if (getcwd(cwd, sizeof(cwd)) != NULL)
		// {
		// 	printf("\033[34m%s ", cwd); // Print the current working directory
			
		// }
		// else
		// {
		// 	perror("getcwd() error");
		// 	return (1);
		// } //////////asta e o incercare de a printa si corect folder dupa prompt, vb cu Marian sa vdm ce paerere are

		// Read user input using readline
		input.line = readline(input.prompt);

		handle_line(&input, data);

		// Add the line to history
		add_history(input.line);

		// Parse the input: separate commands and arguments

		// Execute the parsed commands

		// Free the memory allocated by readline
		free(input.line);
	}
	return (0);
}