
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
#define PROMPT "\033[31mminihell*$>\033[0;34m"

typedef struct s_input
{
	char	*prompt;
	char	*line;
	int		quote_open;

}	t_input;

/// unused for now
typedef struct s_history {
    char *lines[MAX_HISTORY];
    int count;
} t_history;



 ///handle ctrl_commands
void	ctrl_commands();

 // handle line_input
void	handle_line(t_input *input);

	//history
void	create_history(t_history *history, char *line);

 /// built_ins
 void	mini_echo(char **args);
 int	mini_cd(char **args);
 void	mini_pwd(void);
 void	mini_exit(void);


#endif
