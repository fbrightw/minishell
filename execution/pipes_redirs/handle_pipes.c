#include "../../includes/minishell.h"

void	first_process(t_var *var, t_list **pipe_list, int pipes[var->pipe_amount][2], int i)
{
	char *to_token;
	char **args = ((t_in_list*)((*pipe_list)->content))->args;

	dup2(pipes[i][1], 1);
	close(pipes[i][0]);
	close(pipes[i][1]);
	var->path = find_path(var);
	to_token = join_token_slash(args[0]);
	child_work(var, *pipe_list, to_token); //work of execve
}

void	last_process(t_var *var, t_list **pipe_list, int pipes[var->pipe_amount][2], int i)
{
	char *to_token;
	char **args = ((t_in_list*)((*pipe_list)->content))->args;

	dup2(pipes[i-1][0], 0);
	close(pipes[i - 1][0]);
	var->path = find_path(var);
	to_token = join_token_slash(args[0]);
	child_work(var, *pipe_list, to_token); //work of execve
}

void	middle_process(t_var *var, t_list **pipe_list, int  pipes[var->pipe_amount][2], int i)
{
	char *to_token;
	char **args = ((t_in_list*)((*pipe_list)->content))->args;

	dup2(pipes[i][1], 1);
	dup2(pipes[i-1][0], 0);
	close(pipes[i][1]);
	close(pipes[i-1][0]);
	var->path = find_path(var);
	to_token = join_token_slash(args[0]);
	child_work(var, *pipe_list, to_token); //work of execve
}

void	parent_work(int *processes, int pipe_amount, int pipes[pipe_amount][2], int *i)
{
	if (*i == 0)
		close(pipes[*i][1]);
	else if (*i == pipe_amount)
		close(pipes[*i-1][0]);
	else
	{
		close(pipes[*i][1]);
		close(pipes[*i-1][0]);
	}
	*i += 1;
	wait3(&processes[*i], 0, 0);
	// waitid(pids[i], &status, WNOHANG);
}

void	handle_pipes(t_list **pipe_list, t_var *var)
{
	int i;
	int pipe_amount;
	int processes[pipe_amount + 1];
	int pipes[pipe_amount][2];

	i = 0;
	pipe_amount = ft_lstsize(*pipe_list);
	while (i < pipe_amount + 1)
	{
		if (i > 0 && i < pipe_amount)
			(*pipe_list) = (*pipe_list)->next;
		if (i < pipe_amount)
			pipe(pipes[i]);
		processes[i] = fork();
		if (processes[i] == -1)
		{
			printf("ERRROR\n");
			exit(0);
		}
		else if (processes[i] == 0) //child work
		{
			if (i == 0)
				first_process(var, pipe_list, pipes, i);
			else if (i == pipe_amount)
				last_process(var, pipe_list, pipes, i);
			else
				middle_process(var, pipe_list, pipes, i);
		}
		else
			parent_work(processes, pipe_amount, pipes, &i);
	}
}
