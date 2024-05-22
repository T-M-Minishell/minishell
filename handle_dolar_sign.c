
#include "minishell.h"

void	print_pid(void)
{
	pid_t	pid;

	pid = getpid();
	printf("%d: command not found\n", pid);
}

void	handle_dolar(t_list_token *data, int status)
{
	t_list_token *curr;
	int index;

	index = 1;
	curr = data;
//	curr = curr->next;
	if (curr->word[index] == '$')
		print_pid();
	else if (curr->word[index] == '?')
	{
		printf("%d  not done yet\n", status);
	}

}
