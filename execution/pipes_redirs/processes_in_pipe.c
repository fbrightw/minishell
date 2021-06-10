#include "../../includes/minishell.h"

void	deal_with_state(t_var *var, t_list *pipe_list, t_exec *exec_vars, int state)
{
	char	**args;

	args = ((t_in_list *)((pipe_list)->content))->args;
	if (state == 1)
		exec_bin_file(var, var->token, args);
	else if (state == 0)
	{
		if (check_command(var, pipe_list, exec_vars))
			child_work(var, pipe_list, exec_vars);
		else
			exit (0);
	}
	else
		exit (state);
}

void	first_process(t_var *var, t_list *pipe_list, \
	int **pipes, int i)
{
	t_exec	*exec_vars;
	int		state;
	char	**args;
	int		k;

	args = ((t_in_list *)((pipe_list)->content))->args;
	dup2(pipes[i][1], 1);
	k = 0;
	while (k < var->procces_quant - 1)
	{
		close(var->pipes[k][0]);
		close(var->pipes[k][1]);
		k++;
	}
	var->path = find_path(var);
	exec_vars = malloc(sizeof(t_exec));
	exec_vars->to_token = join_token_slash(args[0]);
	var->token = args[0];
	state = check_if_bin_file_in_pipe(var, var->token);
	deal_with_state(var, pipe_list, exec_vars, state);
}

void	last_process(t_var *var, t_list *pipe_list, \
	int **pipes, int i)
{
	t_exec	*exec_vars;
	int		state;
	char	**args;

	args = ((t_in_list *)((pipe_list)->content))->args;
	dup2(pipes[i - 1][0], 0);
	int k = 0;
	while (k < var->procces_quant - 1)
	{
		close(var->pipes[k][0]);
		close(var->pipes[k][1]);
		k++;
	}
	var->path = find_path(var);
	exec_vars = malloc(sizeof(t_exec));
	exec_vars->to_token = join_token_slash(args[0]);
	var->token = args[0];
	state = check_if_bin_file_in_pipe(var, var->token);
	deal_with_state(var, pipe_list, exec_vars, state);
}

void	middle_process(t_var *var, t_list *pipe_list, \
	int **pipes, int i)
{
	t_exec	*exec_vars;
	int		state;
	char	**args;

	args = ((t_in_list *)((pipe_list)->content))->args;
	dup2(pipes[i][1], 1);
	dup2(pipes[i - 1][0], 0);
	int k = 0;
	while (k < var->procces_quant - 1)
	{
		close(var->pipes[k][0]);
		close(var->pipes[k][1]);
		k++;
	}
	var->path = find_path(var);
	exec_vars = malloc(sizeof(t_exec));
	exec_vars->to_token = join_token_slash(args[0]);
	var->token = args[0];
	state = check_if_bin_file_in_pipe(var, var->token);
	deal_with_state(var, pipe_list, exec_vars, state);
}
