#include "../../includes/minishell.h"

char	*go_to(char *env)
{
	while (*env != '=')
		env++;
	return (++env);
}

char 	*find_path(char **env, char *act_path)
{
	int i = 0;
	int j;
	char *path;

	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
		{
			while (env[i][j] == act_path[j])
				j++;
			if (env[i][j] == '=')
			{
				if (j == 4)
					return(go_to(env[i]));
				else
					i++;
			}
			else
				i++;
		}
	}
}

void	putting_fd(t_all *main_struct)
{
	dup2(main_struct->std_fd[1], 1);
	close(1);
}

void	child_work(t_all *main_struct, t_list *inner, char **args, char *token)
{
	char **array_of_path;
	char *temp;
	int i;

	char to_token[ft_strlen(token)+ 2];
	to_token[0] = '/';
	i = 0;

	// merge token and path
	char **env = main_struct->env;
	char *path = find_path(env, "PATH");
	while (token[i])
	{
		to_token[i+1] = token[i];
		i++;
	}
	to_token[i+1] = '\0';

	i = 0;
	if (path)
	{
		array_of_path = ft_split(path, ':');
		while (array_of_path[i])
		{
			path = ft_strdup(array_of_path[i]);
			path = ft_strjoin(path, to_token);
			check_work_redirs(inner, main_struct);
			{
				if (execve(path, args, main_struct->env) == -1)
					i++;
				else
					exit(0);
			}
		}
		write(1, "Didn't find in path\n", 21);
		exit(0);
	}
	else
		write(1, "error\n", 7);
}

void	other_command( t_all *main_struct, t_list *inner, char **args, char *token)
{
	char **env;

	char *path;
	char *temp;

	// env = main_struct->env;
	// path = find_path(env, "PATH");
	pid_t pid = fork(); // create a child;
	// we are in child proccess
	if (pid == 0)
		child_work(main_struct, inner, args, token);
	pid_t pid1 = wait3(&pid, 0, 0);
}
