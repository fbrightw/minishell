#include "../../includes/minishell.h"

void	parent_work(t_var *var, int *i, t_list *pipe_list)
{
	int k = 0;
	while (var->pipes[k])
	{
		close(var->pipes[k][0]);
		close(var->pipes[k][1]);
		k++;
	}
}

void	statuses(t_var *var, int **pipes, int process_quant, int *processes)
{
	int	i;

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
	alloc_mem_for_pipes(var, 1);
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
	alloc_mem_for_pipes(var, 0);
	var->i = 0;
	while (var->i < var->procces_quant)
	{
		if (var->i > 0)
			pipe_list = pipe_list->next;
		if (var->i < var->procces_quant - 1)
			pipe(var->pipes[var->i]);
		var->processes[var->i] = fork();
		if_error(var->processes, var->i);
		if (var->processes[var->i] == 0)
		{
			if (var->i == 0)
				first_process(var, pipe_list, var->pipes, var->i);
			else if (var->i == var->procces_quant - 1)
				last_process(var, pipe_list, var->pipes, var->i);
			else
				middle_process(var, pipe_list, var->pipes, var->i);
		}
		var->i++;
	}
	parent_work(var, &(var->i), pipe_list);
	statuses(var, var->pipes, var->procces_quant, var->processes);
}
