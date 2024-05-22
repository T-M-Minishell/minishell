

#include "minishell.h"

void	print_pid(void)
{
	pid_t	pid;

	pid = getpid();
	printf("%d: command not found\n", pid);
}

void	handle_dolar(t_list_token *data)
{
	t_list_token	*curr;

	curr = data;
	if (strcmp(curr->word, "$") == 0)
	{
		print_pid();
	}
	if (strcmp(curr->word, "?") == 0)
		printf("test\n");
}
