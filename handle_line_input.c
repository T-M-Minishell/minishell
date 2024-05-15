/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/15 14:53:35 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_line(t_input *input)
{
	
	if (input->prompt[0] == '\0')
		return ;
	if (input->line == NULL) // Handle Ctrl-D (EOF)
	{
		printf("exit\n");
		exit(1);
	}
	if (strchr(input->line, '\'') != NULL)
	{	
		if (input->quote_open) {
			input->quote_open = 0;
			input->prompt = "\033[31mminihell*$>\033[0;34m";  // Change back to original prompt
		} else
		{
			input->quote_open = 1;
			input->prompt = ">";
		}
	}
}