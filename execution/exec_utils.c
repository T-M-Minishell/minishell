/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:50:33 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/19 13:08:54 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool check_if_builtin(char *word)
{
    char *arr_of_builtins[] =
		{"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    int num_of_builtins = sizeof(arr_of_builtins) / sizeof(arr_of_builtins[0]);

    for (int i = 0; i < num_of_builtins; i++)
	{
        if (strcmp(word, arr_of_builtins[i]) == 0)
		{
            return true;
        }
    }
    return false;
}

bool check_for_pipe_in_line(t_list_token *data)
{
    int nb_of_pipes = 0;
    t_list_token *curr = data;
    bool is_first = true;
    bool last_was_pipe = false;
            
    while (curr != NULL){
        if (strcmp(curr->word, "|") == 0)
		{
            nb_of_pipes++;
            // Check for pipe at the beginning or double pipes
            if (is_first || last_was_pipe)
                return false;
            last_was_pipe = true;
        }
		else
            last_was_pipe = false;
        is_first = false;
        curr = curr->next;
    }
    // Check for pipe at the end
    if (last_was_pipe || nb_of_pipes == 0)
        return false;
    
    return true;
}