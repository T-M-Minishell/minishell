
#include "minishell.h"

int main(int argc, char **argv)
{
	(void)argv;
	char *prompt = "\033[31mminihell*$>\033[0m ";
	char *line;
	if(argc != 1)
	{
		printf("args are not allowed\n");
		exit(1);
	}
	while (1) {
		// Set up the signal handler for Ctrl+C CTRL-D and CTRL-"\"
		ctrl_commands();
		// Read user input using readline
		line = readline(prompt);  // Consider memory leaks from readline
		if (line == NULL)
		{ // Handle Ctrl-D (EOF)
			printf("exit\n");
			break;
		}
		// Add the line to history
		add_history(line);

		// Parse the input: separate commands and arguments

		// Execute the parsed commands

		// Free the memory allocated by readline
		free(line);
	}
	return 0;
}