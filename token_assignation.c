/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assignation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:51:11 by tlupu             #+#    #+#             */
/*   Updated: 2024/06/15 18:10:42 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_token_to_list(char *line, t_token_type token,
		t_list_token **data)
{
	t_list_token	*new_node;

	if (line == NULL)
	{
		free_token_list(data);
		return ;
	}
	new_node = ft_lstnew(line, token);
	if (new_node == NULL)
	{
		printf("Error allocating node\n");
		free_token_list(data);
		return ;
	}
	ft_lstadd_back(data, new_node);
}
