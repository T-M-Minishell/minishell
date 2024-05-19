/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:37:18 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/15 14:38:50 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int argc, char **argv)
{
	t_input	input;
	(void)argv;
	input.prompt = "\033[31mminihell*$>\033[0;34m";
	if(argc != 1)
	{
		printf("args are not allowed\n");
		exit(1);
	}
	while (1) {
		// Set up the signal handler for Ctrl+C and CTRL-"\"
		ctrl_commands();
		// Read user input using readline
		input.line = readline(input.prompt);
		// handle the line
		handle_line(&input);
		
		// Add the line to history
		add_history(input.line);

		// Parse the input: separate commands and arguments

		// Execute the parsed commands

		// Free the memory allocated by readline
		free(input.line);
	}
	return 0;
}