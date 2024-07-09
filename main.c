/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:37:18 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/09 19:25:33 by msacaliu         ###   ########.fr       */
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

void	check_nb_of_args(int argc)
{
	if (argc != 1)
	{
		printf("Args are not allowed\n");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_input			input;
	t_list_token	*data;
	t_env_var		*env_vars;

	(void)argv;
	check_nb_of_args(argc);
	input.prompt = PROMPT;
	env_vars = get_env_vars(envp);
	print_logo();
	data = NULL;
	while (1)
	{
		ctrl_commands(&input.line);
		input.line = readline(input.prompt);
		if (input.line == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		handle_line(&input, data, &env_vars);
		if (input.line && *input.line)
			add_history(input.line);
		free(input.line);
	}
	return (0);
}
