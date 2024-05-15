
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <termios.h>

#define MAX_HISTORY 100

typedef struct s_input
{
	char	*prompt;
	char	*line;
	int		quote_open;

}	t_input;

// typedef struct s_history {
//     char *lines[MAX_HISTORY];
//     int count;
// } t_history;

 ///handle ctrl_commands
void	ctrl_commands();

 // handle line_input
void	handle_line(t_input *input);


#endif
