#include "../../includes/minishell.h"

char	*find_path(t_var *var)
{
	char	*path;
	char	*env;
	int		i;

	i = 0;
	path = NULL;
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
	char	*to_token;
	int		i;

	i = 0;
	to_token = malloc(sizeof(char) * (ft_strlen(token) + 2));
	to_token[0] = '/';
	while (token[i])
	{
		to_token[i + 1] = token[i];
		i++;
	}
	to_token[i + 1] = '\0';
	return (to_token);
}

void	freeing(t_exec *exec_vars, t_var *var)
{
	int	i;

	i = 0;
	free(exec_vars->to_token);
	while (exec_vars->array_of_path[i])
	{
		if (exec_vars->array_of_path[i])
			free(exec_vars->array_of_path[i]);
		i++;
	}
	free(exec_vars->array_of_path);
	free(exec_vars);
	free(var->path);
}

