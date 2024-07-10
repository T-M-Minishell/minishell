/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions_exec.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:44:29 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 12:58:47 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_command_list(t_list_commands *cmd_head)
{
	t_list_commands	*temp;
	int				i;

	while (cmd_head != NULL)
	{
		temp = cmd_head;
		cmd_head = cmd_head->next;
		i = 0;
		while (temp->arr[i])
		{
			free(temp->arr[i]);
			i++;
		}
		free(temp->arr);
		free(temp);
	}
}
