#include "../../includes/minishell.h"

void	first_process(t_var *var, t_list *pipe_list, int pipes[var->pipe_amount][2], int i)
{
	t_exec *exec_vars;
	char **args = ((t_in_list*)((pipe_list)->content))->args;

	dup2(pipes[i][1], 1);
	close(pipes[i][0]);
	close(pipes[i][1]);
	var->path = find_path(var);
	exec_vars = malloc(sizeof(t_exec));
	exec_vars->to_token = join_token_slash(args[0]);
	var->token = args[0];
	if (check_command(var, pipe_list, exec_vars))
		child_work(var, pipe_list, exec_vars); //work of execve
	else
		exit(0);
}

void	last_process(t_var *var, t_list *pipe_list, int pipes[var->pipe_amount][2], int i)
{
	t_exec *exec_vars;
	char **args = ((t_in_list*)((pipe_list)->content))->args;

	dup2(pipes[i-1][0], 0);
	close(pipes[i - 1][0]);
	var->path = find_path(var);
	exec_vars = malloc(sizeof(t_exec));
	exec_vars->to_token = join_token_slash(args[0]);
	var->token = args[0];
	if (check_command(var, pipe_list, exec_vars))
		child_work(var, pipe_list, exec_vars); //work of execve
	else
		exit(0);
}

void	middle_process(t_var *var, t_list *pipe_list, int pipes[var->pipe_amount][2], int i)
{
	t_exec *exec_vars;
	char **args = ((t_in_list*)((pipe_list)->content))->args;

	dup2(pipes[i][1], 1);
	dup2(pipes[i-1][0], 0);
	close(pipes[i][1]);
	close(pipes[i-1][0]);
	var->path = find_path(var);
	exec_vars->to_token = join_token_slash(args[0]);
	var->token = args[0];
	if (check_command(var, pipe_list, exec_vars))
		child_work(var, pipe_list, exec_vars); //work of execve
	else
		exit(0);
}

void	parent_work(int *processes, int process_quant, int pipes[process_quant - 1][2], int *i)
{
	if (*i == 0)
		close(pipes[*i][1]);
	else if (*i == process_quant - 1)
		close(pipes[*i-1][0]);
	else
	{
		close(pipes[*i][1]);
		close(pipes[*i-1][0]);
	}
	*i += 1;
}

void	statuses(t_var *var, int process_quant, int *processes)
{
	int i;

	i = 0;
	while (i < process_quant)
	{
		waitpid(processes[i], &(var->status), 0);
		if (i == process_quant - 1)
		{
			if (WIFEXITED(var->status))
				var->status = WEXITSTATUS(var->status);
			else if (WIFSIGNALED(var->status))
				var->status = WTERMSIG(var->status) + 128;
		}
		i++;
	}
}

void	if_error(int *processes, int i)
{
	if (processes[i] == -1)
	{
		printf("ERRROR\n");
		exit(0);
	}
}

void	handle_pipes(t_list *pipe_list, t_var *var)
{
	int i;
	int process_quant = ft_lstsize(pipe_list);
	int processes[process_quant];
	int pipes[process_quant - 1][2];

	i = 0;
	while (i < process_quant)
	{
		if (i > 0)
			pipe_list = pipe_list->next;
		if (i < process_quant - 1)
			pipe(pipes[i]);
		processes[i] = fork();
		if_error(processes, i);
		if (processes[i] == 0) //child work
		{
			if (i == 0)
				first_process(var, pipe_list, pipes, i);
			else if (i == process_quant - 1)
				last_process(var, pipe_list, pipes, i);
			else
				middle_process(var, pipe_list, pipes, i);
		}
		else
			parent_work(processes, process_quant, pipes, &i);
	}
	statuses(var, process_quant, processes);
}
