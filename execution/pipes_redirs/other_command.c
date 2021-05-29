#include "../../includes/minishell.h"

void	child_work(t_var *var, t_list *pipe_list, char *to_token)
{
	char **array_of_path;
	int i;
	char *path_with_cmd;
	char **args = ((t_in_list*)((pipe_list)->content))->args;

	i = 0;
	if (var->path)
	{
		array_of_path = ft_split(var->path, ':');
		while (array_of_path[i])
		{
			path_with_cmd = ft_strdup(array_of_path[i]);
			path_with_cmd = ft_strjoin(path_with_cmd, to_token);
			check_work_redirs(pipe_list);
			if (execve(path_with_cmd, args, var->general->envs->env_arr) == -1)
				i++;
			else
				exit(0);
		}
		write(1, "Didn't find in path\n", 21);
		exit(0);
	}
	else
		write(1, "error\n", 7);
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

void	other_command(t_var *var, t_list *pipe_list, char *token)
{
	char *env;
	char *to_token;
	int i;

	i = 0;
	var->path = find_path(var);
	to_token = join_token_slash(token);
	pid_t pid = fork(); // create a child;
	if (pid == 0)
		child_work(var, pipe_list, to_token);
	pid_t pid1 = wait3(&pid, 0, 0);
}
