/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:17:42 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/16 13:24:47 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_history(t_history *history,char *line)
{
    if (history->count < MAX_HISTORY)
	{
        history->lines[history->count++] = strdup(line);
    }
	else
	{
        free(history->lines[0]);
        for (int i = 1; i < MAX_HISTORY; i++)
            history->lines[i - 1] = history->lines[i];
        history->lines[MAX_HISTORY - 1] = strdup(line);
    }
}