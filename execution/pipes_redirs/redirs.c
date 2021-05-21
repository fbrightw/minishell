#include "../../includes/minishell.h"

int	redir_outputs(t_all *main_struct, char *file, char *type)
{
	// close(STDOUT);
		// printf("%s\n", file);
	if (!strcmp(type, "OUTPUT"))
		main_struct->file_fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
	{
		printf("file %s\n", file);
		main_struct->file_fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	}

	// printf("%d\n", main_struct->std_fd[1]);
	// if (main_struct->std_fd[1] == -1)
	// {
		// ERROR
	// }
	main_struct->std_fd[1] = dup2(main_struct->file_fd, STDOUT);
	close(main_struct->file_fd);
	return (1);
}

void	redir_input(t_all *main_struct, char *file)
{
	// close(main_struct->std_fd[0]); //close stdin
	main_struct->file_fd = open(file, O_RDONLY);
	// if (main_struct->std_fd[1] == -1)
	// {
		// ERROR
	// }
	main_struct->std_fd[0] = dup2(main_struct->file_fd, STDIN);
	close(main_struct->file_fd);
}
