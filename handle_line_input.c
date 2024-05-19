/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/19 17:17:56 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_pid(void)
{
	pid_t	pid;

	pid = getpid();
	printf("%d: command not found\n",pid);
}

void	handle_line(t_input *input)
{
	char *args[99];
	
	int i;

	i = 0;
		
	// Handle Ctrl-D (EOF)
	if (input->line == NULL) 
	{
		printf("exit\n");
		exit(1);
	}
	args[i] = strtok(input->line, " "); //tokenize with space as delimiter ..

	while(args[i] != NULL)
	{
		i++;
		args[i] = strtok(NULL, " ");
	}
	if (args[0] != NULL)
	{
		if (strcmp(args[0], "echo") == 0)
        	mini_echo(args);
		if (strcmp(args[0], "cd") == 0)
			mini_cd(args);
		if (strcmp(args[0], "pwd") == 0)
			mini_pwd();
		if (strcmp (args[0], "exit") == 0)
			mini_exit();
	}
		



	
	// i = -1;
//	while (++input->line[i])
//	{
//		if(input->line[i] == '$' && input->line[i+1] == '$')
//		{
//			print_pid();
//		}
//		if()
//	}


}