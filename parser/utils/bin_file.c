#include "../../includes/minishell.h"

int	check_if_bin_file(t_var *var, char *word)
{
	struct stat	buffer;

	if (ft_strchr(word, '/'))
	{
		if (!stat(word, &buffer) && !S_ISDIR(buffer.st_mode))
			return (1);
		else if (!stat(word, &buffer) && S_ISDIR(buffer.st_mode))
		{
			ft_putendl_fd("is a directory", 2);
			var->status = 126;
			return (2);
		}
		else if (stat(word, &buffer) < 0)
		{
			ft_putendl_fd("no such file or directory", 2);
			var->status = 127;
			return (3);
		}
	}
	return (0);
}

int	check_if_bin_file_in_pipe(t_var *var, char *word)
{
	struct stat	buffer;

	if (ft_strchr(word, '/'))
	{
		if (!stat(word, &buffer) && !S_ISDIR(buffer.st_mode))
			return (1);
		else if (!stat(word, &buffer) && S_ISDIR(buffer.st_mode))
		{
			ft_putendl_fd("is a directory", 2);
			return (126);
		}
		else if (stat(word, &buffer) < 0)
		{
			ft_putendl_fd("no such file or directory", 2);
			return (127);
		}
	}
	return (0);
}

void	exec_bin_file(t_var *var, char *bin, char **args)
{
	execve(bin, args, var->general->envs->env_arr);
	ft_putendl_fd(strerror(errno), 2);
	exit (126);
}

void	not_bin_file(t_list *pipe_list, t_var *var, char **args)
{
	int	i;

	i = 0;
	while (var->general->envs->env_arr[i])
	{
		if (!ft_strncmp(var->general->envs->env_arr[i], "PATH=", 5))
		{
			path_exist(pipe_list, var, args);
			return ;
		}
		i++;
	}
	var->status = 127;
	printf("%s %s\n", var->token, ": command not found");
}
