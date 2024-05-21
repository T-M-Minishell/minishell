/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   un_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:22:13 by tlupu             #+#    #+#             */
/*   Updated: 2024/05/21 22:41:59 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **turn_word_into_arr(t_list_token *data)
{
    int i = 0;
    char **arr;
    t_list_token *curr;
    curr = data->next;
    while (curr != NULL)
    {
        i++;
        curr = curr->next;
    }
    arr = malloc((i + 1) * sizeof(char *));
    if (arr == NULL)
        return(0);
    curr = data->next;
    i = 0;
    while (curr != NULL)
    {
        arr[i++] = curr->word;
        curr = curr->next;
    }
    arr[i] = NULL;
    return(arr);
}

void    mini_ls(char **arr)
{
    pid_t pid;
    char *path = "/bin/ls";

    pid = fork();
    if (pid < 0)
        perror("ERROR WITH PID\n");
    else if (pid == 0)
        execv(path, arr); 
    else
        wait(NULL);
}

void   handle_not_existent_builtins(t_list_token *data)
{

    t_list_token *curr = NULL;
    curr = data->next;
    char **arr;
    
    arr = turn_word_into_arr(curr);
    if(arr == NULL)
        return;
    if (curr->word != NULL)
    {
        if (strcmp(curr->word, "ls") == 0)
            mini_ls(arr);
    }
}
