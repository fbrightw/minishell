#include "../../includes/minishell.h"

int	redir_outputs(t_reds *reds, char *type)
{
	// if (main_struct->std_fd[1] == -1)
	// {
		// ERROR
	// }
	dup2(reds->file_fd, STDOUT);
	close(reds->file_fd);
	return (1);
}

void	redir_input(t_reds *reds)
{
	// if (main_struct->std_fd[1] == -1)
	// {
		// ERROR
	// }
	dup2(reds->file_fd, STDIN);
	close(reds->file_fd);
}
