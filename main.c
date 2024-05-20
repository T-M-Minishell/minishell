/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:37:18 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/20 14:48:46 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int argc, char **argv)
{
	t_input	input;
	(void)argv;
	input.prompt = PROMPT;

	// todor s main ---------------
	t_token_type	token;
	t_list_token	*data;
	// t_list_token	*curr;
	data = ft_lstnew_init();
 //------------------
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
		
		while ((token = check_token(input.line, &data)) != END)
		{
			assign_token_to_list(input.line, token, &data);
			
		}
		handle_line(&input, data);
		
	
		// handle the line

		//todor;s -----------
		// while ((token = check_token(input.line, &data)) != END)
		// 	assign_token_to_list(input.line, token, &data);
		// curr = data->next;//de dbug
		// while (curr != NULL && curr->word != NULL)
		// {
		// 	printf("%s\n", curr->word);
		// 	curr = curr->next;
		// }
//  / ----------------------------
		
		
		// Add the line to history
		add_history(input.line);

		// Parse the input: separate commands and arguments

		// Execute the parsed commands

		// Free the memory allocated by readline
		free(input.line);
	}
	return 0;
}