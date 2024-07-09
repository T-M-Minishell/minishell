/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:50:33 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/09 17:12:29 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_if_builtin(char *word)
{
	int	num_of_builtins;
	int	i;

	i = 0;
	char *arr_of_builtins[] =
		{"echo","cd","export", "unset", "env", "exit","pwd"};

	num_of_builtins = sizeof(arr_of_builtins) / sizeof(arr_of_builtins[0]);

	while (i < num_of_builtins)
	{
		if (strcmp(word, arr_of_builtins[i]) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_for_pipe_in_line(t_list_token *data)
{
	int				nb_of_pipes;
	t_list_token	*curr;
	bool			is_first;
	bool			last_was_pipe;

	nb_of_pipes = 0;
	curr = data;
	last_was_pipe = false;
	is_first = true;
	while (curr != NULL)
	{
		if (strcmp(curr->word, "|") == 0)
		{
			nb_of_pipes++;
			if (is_first || last_was_pipe)
				return (false);
			last_was_pipe = true;
		}
		else
			last_was_pipe = false;
		is_first = false;
		curr = curr->next;
	}
	if (last_was_pipe || nb_of_pipes == 0)
		return (false);
	return (true);
}


bool	check_for_redirects_in_line(t_list_token *data)
{
	t_list_token	*curr;
	bool			is_first;
	bool			last_was_redirect;
	int				nb_of_redirects;

	curr = data;
	is_first = true;
	last_was_redirect = false;
	nb_of_redirects = 0;
	while (curr != NULL)
	{
		if (strcmp(curr->word, ">") == 0 || strcmp(curr->word, ">>") == 0
			|| strcmp(curr->word, "<") == 0 || strcmp(curr->word, "<<") == 0)
		{
			nb_of_redirects++;
			if (is_first || last_was_redirect)
				return (false);
			last_was_redirect = true;
		}
		else
			last_was_redirect = false;
		is_first = false;
		curr = curr->next;
	}
	if (last_was_redirect || nb_of_redirects == 0)
		return (false);
	return (true);
}
