/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:05 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/02 14:46:23 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


// void ctrl_c_handler(int sig) {
//     // (void)sig;
//     if (sig == SIGINT)
// 	{
//         tcflush(STDIN_FILENO, TCIOFLUSH);
//         write(STDOUT_FILENO, "\n", 1);
//         write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);  // Print prompt without newline
// 	}

//     // write(STDOUT_FILENO, "\n", 1);  // Print newline for clean prompt display
//     // write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);  // Print prompt without newline
// }

// void	ctrl_commands()
// {
// 	signal(SIGQUIT, SIG_IGN);//pdf asks to do nothing -CREL-"\"
// 	// signal(SIGINT,ctrl_c_handler);
//     struct sigaction	sa_ctrl_c;

//     sa_ctrl_c.sa_handler = &ctrl_c_handler;
// 	sa_ctrl_c.sa_flags = SA_RESTART;
// 	sigemptyset(&sa_ctrl_c.sa_mask);
// 	sigaction(SIGINT, &sa_ctrl_c, NULL);
// 	signal(SIGUSR1, SIG_IGN);

// }

void ctrl_c_handler(int sig, siginfo_t *info, void *context) {
    (void)info;
    (void)context;
    if (sig == SIGINT) {
        // Clear the input buffer
        rl_replace_line("", 0);
        // rl_redisplay();
        write(STDOUT_FILENO, "\n", 1);
        write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
    }
}

void ctrl_commands(char **line){
   (void)line;
    struct sigaction sa_ctrl_c;

    sa_ctrl_c.sa_sigaction = ctrl_c_handler;
    sa_ctrl_c.sa_flags = SA_SIGINFO | SA_RESTART;
    sigemptyset(&sa_ctrl_c.sa_mask);
    sigaction(SIGINT, &sa_ctrl_c, NULL);
    signal(SIGQUIT, SIG_IGN);  // Ignore SIGQUIT
    signal(SIGUSR1, SIG_IGN);  // Ignore SIGUSR1
}
