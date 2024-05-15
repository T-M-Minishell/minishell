/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:17:42 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/15 14:22:03 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void add_history(t_history *history, const char *line)
// {
//     if (history->count < MAX_HISTORY)
// 	{
//         history->lines[history->count++] = strdup(line);
//     }
// 	else
// 	{
//         free(history->lines[0]);
//         for (int i = 1; i < MAX_HISTORY; i++)
//             history->lines[i - 1] = history->lines[i];
//         history->lines[MAX_HISTORY - 1] = strdup(line);
//     }
// }