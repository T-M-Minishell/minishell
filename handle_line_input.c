/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/15 14:57:54 by msacaliu         ###   ########.fr       */
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
	int i;

	if (input->prompt[0] == '\0')
		return ;
	if (input->line == NULL) // Handle Ctrl-D (EOF)
	{
		printf("exit\n");
		exit(1);
	}
	i = -1;
//	while (++input->line[i])
//	{
//		if(input->line[i] == '$' && input->line[i+1] == '$')
//		{
//			print_pid();
//		}
//		if()
//	}


}