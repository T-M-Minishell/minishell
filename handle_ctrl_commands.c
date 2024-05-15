/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:05 by msacaliu          #+#    #+#             */
/*   Updated: 2024/05/15 14:38:20 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ctrl_c_handler(int num)
{
	(void)num;
	printf("\n\033[31mminihell*$>\033[0;34m");


}
// void ctrl_c_handler(int signum, siginfo_t *info, void *context) {
//     (void)context;
//     (void)(info->si_pid);
// 	(void) (signum);
// 	printf("\033[31mminihell*$>\033[0;34m");
// }
void	ctrl_commands()
{
	// (void) input;
	
	// // int num = 0;
	signal(SIGQUIT, SIG_IGN);//pdf asks to do nothing
	signal(SIGINT,ctrl_c_handler);


	// int val = 1;
	// struct sigaction sa;

    // memset(&sa, 0, sizeof(struct sigaction));
    // sa.sa_flags = SA_SIGINFO;
    // sa.sa_sigaction = ctrl_c_handler;

    // if (sigaction(SIGINT, &sa, NULL) == -1) {
    //     val = 1;
    // }

    // // while (1) {
    // //     pause();  // Wait for signals
    // // }
	// if(val == 1)
	// 	input->line = "\033[31mminihell*$>\033[0;34m";
}



