/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:05 by msacaliu          #+#    #+#             */
/*   Updated: 2024/06/10 14:37:14 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void ctrl_c_handler(int sig) {
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);  // Print newline for clean prompt display
    write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);  // Print prompt without newline
}

void	ctrl_commands()
{
	signal(SIGQUIT, SIG_IGN);//pdf asks to do nothing -CREL-"\"
	signal(SIGINT,ctrl_c_handler);

}
