#include "../../includes/minishell.h"

int		check_if_bin_file(char *word)
{
	if (word[0] == '.' || word[1] == '\\')
		return (1);
	return (0);
}

void	child_work(t_var *var, t_list *pipe_list, t_exec *exec_vars)
{
	int i;
	char **args = ((t_in_list*)((pipe_list)->content))->args;

	signal(SIGQUIT, SIG_DFL);//ctrl+/
	signal(SIGINT, SIG_DFL); //ctrl+c
	i = 0;
	check_work_redirs(pipe_list, var);
	if (!check_if_bin_file(var->token))
	{
		if (var->path)
		{
			exec_vars->array_of_path = ft_split(var->path, ':');
			while (exec_vars->array_of_path[i])
			{
				exec_vars->path_with_cmd = ft_strdup(exec_vars->array_of_path[i]);
				exec_vars->path_with_cmd = ft_strjoin(exec_vars->path_with_cmd, exec_vars->to_token);
				if (execve(exec_vars->path_with_cmd, args, var->general->envs->env_arr) == -1)
					i++;
			}
		}
		else
		{
			write(1, "error\n", 7);
			exit(0);
		}
	}
	else
	{
		execve(var->token, args, var->general->envs->env_arr);
		printf("%s\n", strerror(errno));
		// exit(126);
	}
}

char	*find_path(t_var *var)
{
	char *path = NULL;
	char *env;
	int i;

	i = 0;
	while (var->general->envs->env_arr[i])
	{
		if (!ft_strncmp(var->general->envs->env_arr[i], "PATH", 4))
		{
			env = ft_strdup(var->general->envs->env_arr[i]);
			path = ft_substr(env, 5, (ft_strlen(env) - ft_strlen("PATH")));
		}
		i++;
	}
	return (path);
}

char	*join_token_slash(char *token)
{
	char *to_token;
	int i;

	i = 0;
	to_token = malloc(sizeof(char) * (ft_strlen(token) + 2));
	to_token[0] = '/';
	while (token[i])
	{
		to_token[i+1] = token[i];
		i++;
	}
	to_token[i+1] = '\0';
	return (to_token);
}

void	freing(t_exec *exec_vars, t_var *var)
{
	free(exec_vars->to_token);
	free(exec_vars);
	free(var->path);
}

int	check_command(t_var *var, t_list *pipe_list, t_exec *exec_vars)
{
	struct stat *buffer;
	int i;

	i = 0;
	buffer = malloc(sizeof(struct stat));
	if (var->path)
	{
		exec_vars->array_of_path = ft_split(var->path, ':');
		while (exec_vars->array_of_path[i])
		{
			exec_vars->path_with_cmd = ft_strdup(exec_vars->array_of_path[i]);
			exec_vars->path_with_cmd = ft_strjoin(exec_vars->path_with_cmd, exec_vars->to_token);
			if (stat(exec_vars->path_with_cmd , buffer) == 0)
				return (1);
			else
				i++;
		}
		if (S_ISDIR(buffer->st_mode))
		{
			var->status = 127;
			printf("command not found\n");
		}
		else
		{
			var->status = 127;
			printf("%s %s\n", var->token, ": command not found");
		}
		return (0);
	}
}

void	other_command(t_var *var, t_list *pipe_list, char *token)
{
	t_exec *exec_vars;
	char *env;
	int i;

	i = 0;
	exec_vars = malloc(sizeof(t_exec));
	var->path = find_path(var);
	exec_vars->to_token = join_token_slash(token);
	if (check_command(var, pipe_list, exec_vars))
	{
		pid_t pid = fork();
		if (pid == 0)
			child_work(var, pipe_list, exec_vars);
		waitpid(pid, &(var->status), 0);
		freing(exec_vars, var);
		if (WIFEXITED(var->status))
			var->status = WEXITSTATUS(var->status);
		else if (WIFSIGNALED(var->status))
			var->status = WTERMSIG(var->status) + 128;
		else if (WIFSTOPPED(var->status))
			var->status = 128 + WSTOPSIG(var->status);
	}
}
