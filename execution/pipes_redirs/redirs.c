#include "../../includes/minishell.h"

void	redir_output(t_into_lists *vars, t_all *main_struct, char *args)
{
	close(main_struct->std_fd[1]);
	main_struct->std_fd[1] = open(args, O_CREAT | O_WRONLY | O_TRUNC);
	// if (main_struct->std_fd[1] == -1)
	// {
		// ERROR
	// }
	// dup2(main_struct->std_fd[1], STDOUT);
}

void	redir_input(t_into_lists *vars, t_all *main_struct, char **args, char *redir)
{
	close(main_struct->std_fd[0]);
	if (strcmp(redir, "INPUT"))
		main_struct->std_fd[0] = open(args, O_CREAT | O_WRONLY | O_TRUNC);
	else
		main_struct->std_fd[0] = open(args, O_CREAT | O_WRONLY | O_APPEND);
	// if (main_struct->std_fd[1] == -1)
	// {
		// ERROR
	// }
	// dup2(main_struct->std_fd[0], STDIN);
}

void	redirs(t_list *com_in_str, t_into_lists *vars, t_all *main_struct, t_var *var)
{
	int index;
	int i;
	int j;

	i = 0;
	j = 0;
	main_struct->std_fd[0] = 0; //stdin
	main_struct->std_fd[1] = 1; //stdout
	while (vars->redirs[i])
	{
		func(com_in_str, main_struct, var, vars->args[j]);
		index = vars->redirs[i];
		if (strcmp(vars->args[index], ">"))
			redir_output(vars, main_struct, (*(vars->args) + index + 1));
		else if (strcmp(vars->args[index], "<")) // input
			redir_input(vars, main_struct, (*(vars->args) + index + 1), "INPUT");
		else
			redir_input(vars, main_struct, (*(vars->args) + index + 1), "APP_INPUT");
		j += index + 1;
	}
}
