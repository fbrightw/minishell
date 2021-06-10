#include "../includes/minishell.h"

void	handle_signal_slash(int sig)
{
	(void)(sig);
}

void	handle_signal_c(int sig)
{
	if (sig == 2)
		g_flag = 1;
}
