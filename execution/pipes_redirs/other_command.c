#include "../../includes/minishell.h"

void	child_finding_in_path(t_exec *ex, t_var *var, char **args)
{
	var->i = 0;
	while (ex->array_of_path[var->i])
	{
		ex->path_with_cmd = ft_strdup(ex->array_of_path[var->i]);
		ex->path_with_cmd = ft_strjoin(ex->path_with_cmd, ex->to_token);
		if (execve(ex->path_with_cmd, \
		args, var->general->envs->env_arr) == -1)
			var->i++;
	}
	exit (0);
}

void	child_work(t_var *var, t_list *pipe_list, t_exec *ex)
{
	char	**args;

	args = ((t_in_list *)((pipe_list)->content))->args;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	check_work_redirs(pipe_list, var);
	if (!check_if_bin_file(var, var->token))
	{
		if (var->path)
			child_finding_in_path(ex, var, args);
		else
		{
			write(1, "error\n", 7);
			exit(0);
		}
	}
	exec_bin_file(var, var->token, args);
}

int	finding_in_path(t_exec *exec_vars, struct stat *buffer)
{
	int	i;

	i = 0;
	while (exec_vars->array_of_path[i])
	{
		exec_vars->path_with_cmd = \
		ft_strdup(exec_vars->array_of_path[i]);
		exec_vars->path_with_cmd = \
		ft_strjoin(exec_vars->path_with_cmd, exec_vars->to_token);
		if (stat(exec_vars->path_with_cmd, buffer) == 0)
		{
			free(exec_vars->path_with_cmd);
			return (1);
		}
		else
		{
			free(exec_vars->path_with_cmd);
			i++;
		}
	}
	return (0);
}

int	check_command(t_var *var, t_list *pipe_list, t_exec *exec_vars)
{
	struct stat	buffer;

	if (var->path)
	{
		exec_vars->array_of_path = ft_split(var->path, ':');
		if (!finding_in_path(exec_vars, &buffer))
		{
			if (S_ISDIR(buffer.st_mode))
			{
				var->status = 126;
				// write(2, "", 1);
				// printf("command not found\n");
			}
			else
			{
				var->status = 127;
				printf("%s %s\n", var->token, ": command not found");
			}
			return (0);
		}
		return (1);
	}
	return (0);
}

void	other_command(t_var *var, t_list *pipe_list, char *token)
{
	t_exec	*exec_vars;
	char	*env;
	int		i;
	pid_t	pid;

	i = 0;
	exec_vars = malloc(sizeof(t_exec));
	var->path = find_path(var);
	exec_vars->to_token = join_token_slash(token);
	if (check_command(var, pipe_list, exec_vars))
	{
		pid = fork();
		if (pid == 0)
			child_work(var, pipe_list, exec_vars);
		waitpid(pid, &(var->status), 0);
		if (WIFEXITED(var->status))
			var->status = WEXITSTATUS(var->status);
		else if (WIFSIGNALED(var->status))
			var->status = WTERMSIG(var->status) + 128;
		else if (WIFSTOPPED(var->status))
			var->status = 128 + WSTOPSIG(var->status);
	}
	freeing(exec_vars, var);
}
