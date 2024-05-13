
#include "minishell.h"

int main() {
	char *prompt = "minishell$ ";
	char *line;

	while (1) {
		// Print the prompt
		printf("%s", prompt);

		// Read user input using readline
		line = readline("");  // Consider memory leaks from readline

		if (line == NULL) {  // Handle Ctrl-D (EOF)
			break;
		}

		// Add the line to history
		add_history(line);

		// Parse the input: separate commands and arguments
		// (implementation details in next step)

		// Execute the parsed commands
		// (implementation details in next step)

		// Free the memory allocated by readline
		free(line);
		//heeeeeey
	}
	return 0;
}