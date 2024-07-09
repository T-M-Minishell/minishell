/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:37:18 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/09 11:26:55 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errno.h"

void	print_logo(void)
{
	printf("\033[1m\033[31m");
	printf("		.----------------.  .----------------.  .-----------------. .----------------.  .----------------.  .----------------.  .----------------.  .----------------. \n");
	printf("		| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
	printf("		| | ____    ____ | || |     _____    | || | ____  _____  | || |     _____    | || |  ____  ____  | || |  _________   | || |   _____      | || |   _____      | |\n");
	printf("		| ||_   \\  /   _|| || |    |_   _|   | || ||_   \\|_   _| | || |    |_   _|   | || | |_   ||   _| | || | |_   ___  |  | || |  |_   _|     | || |  |_   _|     | |\n");
	printf("		| |  |   \\/   |  | || |      | |     | || |  |   \\ | |   | || |      | |     | || |   | |__| |   | || |   | |_  \\_|  | || |    | |       | || |    | |       | |\n");
	printf("		| |  | |\\  /| |  | || |      | |     | || |  | |\\ \\| |   | || |      | |     | || |   |  __  |   | || |   |  _|  _   | || |    | |   _   | || |    | |   _   | |\n");
	printf("		| | _| |_\\/_| |_ | || |     _| |_    | || | _| |_\\   |_  | || |     _| |_    | || |  _| |  | |_  | || |  _| |___/ |  | || |   _| |__/ |  | || |   _| |__/ |  | |\n");
	printf("		| ||_____||_____|| || |    |_____|   | || ||_____|\\____| | || |    |_____|   | || | |____||____| | || | |_________|  | || |  |________|  | || |  |________|  | |\n");
	printf("		| |              | || |              | || |              | || |              | || |              | || |              | || |              | || |              | |\n");
	printf("		| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
	printf(" 		'----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n");
	printf("\n										** MiniShell **\n");
}


int main(int argc, char **argv, char **envp)
{
	t_input input;
	t_list_token *data;
	env_var *env_vars = NULL;
	(void)argv;
	// int	last_exit_status;
	
	// last_exit_status = 0;
	input.prompt = PROMPT;

	// Initialize environment variables
	env_vars = get_env_vars(envp); // works

	// update_shlvl(env_vars) {
	//	
	
	//}

	// Initialize token list
	if (argc != 1) {
		printf("Args are not allowed\n");
		exit(1);
	}
	print_logo();
	data = NULL;
	while (1)
	{
		// Set up the signal handler for Ctrl+C and CTRL-"\"
		ctrl_commands(&input.line);
		// Read user input using readline
		input.line = readline(input.prompt);
		if (input.line == NULL)
		{
			printf("exit\n");
			exit(1);
        }	
		handle_line(&input, data, &env_vars);
		// Add the line to history
		if (input.line && *input.line)
			add_history(input.line);
		// Free the memory allocated by readline
		free(input.line);		
	}
	return 0;
}
