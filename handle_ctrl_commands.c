
#include "minishell.h"

void	ctrl_c_handler(int num)
{
	(void)num;
	printf("\n\033[31mminihell*$>\033[0m");

}
void	ctrl_commands()
{
	signal(SIGQUIT, SIG_IGN);//pdf asks to do nothing
	signal(SIGINT, ctrl_c_handler);
}



