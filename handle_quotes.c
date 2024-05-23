/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:11:33 by tlupu             #+#    #+#             */
/*   Updated: 2024/05/23 17:39:49 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_echo_quote(t_list_token *data)
{
	t_list_token *curr;

	curr = data;
	if (curr->next == NULL)
		printf("\n");
	else
	{
		curr = curr->next;
		int	print_new_line = 1;
		//check for -n function
		if(curr->quotes != NULL && strcmp(curr->quotes, "-n") == 0)
		{

			print_new_line = 0; //supress new_line when -n
			curr = curr->next;
		}
		while(curr->quotes != NULL)  /// problem here when i put quotes
		{
			printf("%s ", curr->quotes);
			curr = curr->next;
		}
		// print new_line if -n is not specified
		if(print_new_line)
			printf("\n");
	}
}