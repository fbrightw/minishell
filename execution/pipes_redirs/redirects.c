#include "../../includes/minishell.h"

int	redir_outputs(t_reds *reds, char *type)
{
	char *file_name = reds->redir;
	if (!strcmp(type, "OUTPUT"))
		reds->file_fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
	{
		printf("file %s\n", file_name);
		reds->file_fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0777);
	}

	// printf("%d\n", main_struct->std_fd[1]);
	// if (main_struct->std_fd[1] == -1)
	// {
		// ERROR
	// }
	reds->std_fd[1] = dup2(reds->file_fd, STDOUT);
	close(reds->file_fd);
	return (1);
}

void	redir_input(t_reds *reds)
{
	char *file_name = reds->redir;
	// close(main_struct->std_fd[0]); //close stdin
	reds->file_fd = open(file_name, O_RDONLY);
	// if (main_struct->std_fd[1] == -1)
	// {
		// ERROR
	// }
	reds->std_fd[0] = dup2(reds->file_fd, STDIN);
	close(reds->file_fd);
}
