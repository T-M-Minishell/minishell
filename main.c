
#include "minishell.h"

int main() {
	char *prompt = "minishell$ ";
	char *line1;

	while (1) {
		// Print the prompt
		printf("%s", prompt);

		// Read user input using readline
		line1 = readline("");  // Consider memory leaks from readline

		if (line1 == NULL) {  // Handle Ctrl-D (EOF)
			break;
		}

		for (int i = 0; i < 5; i++)
			printf("here");
		// Add the line to history
		add_history(line1);

		// Parse the input: separate commands and arguments
		// (implementation details in next step)

		// Execute the parsed commands
		// (implementation details in next step)

		// Free the memory allocated by readline
		free(line1);
		//heeeeeey
		//heeeei
		//heiiiii
	}
	return 0;
}