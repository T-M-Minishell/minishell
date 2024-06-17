/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:34:38 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/17 19:52:54 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_command {
    char **args; // Array of strings representing the command and its arguments
	char *word;
    int arg_count; // Number of arguments in the command
} t_command;


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


void arr_of_commands(t_list_token *data)
{
	t_list_token *curr;

	curr = data;
	while (curr != NULL)
	{
		if(strcmp(curr->word, "|") == 0)
			break;
		printf("--%s\n",curr->word);
		curr = curr->next;
	}
	curr = curr->next;
	printf("curr: %s\n",curr->word);
}

void	handle_pipe(char *line,t_list_token *data, env_var **vars)
{
	t_command 		*cmd;
	t_list_token	*curr;

	(void)cmd;
	(void)vars;
	(void)line;
	curr = data;
	arr_of_commands(curr);

	
}