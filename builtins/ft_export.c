#include "../includes/minishell.h"

void	print_export(char **env)
{
	int		i;
// добавь кавычки, чел
	i = 0;
	while (env[i])
	{
		write(1,"declare -x ", 12);
		write(1, env[i], ft_strlen(env[i]));
		write(1,"\n",1);
		i++;
	}
}

char	**sort_export(char **env)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	len = get_arr_len(env);
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strncmp(env[j], env[j + 1], ft_strlen(env[j])) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

char	**copy_env(char **env)
{
	char	**new_arr;
	int		row;
	int		i;

	row = get_arr_len(env);
	new_arr = malloc((row + 1) * sizeof(char*));
	i = 0;
	while (env[i])
	{
		new_arr[i] = ft_strdup(env[i]);
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

void	ft_export(t_all main_struct, char **args)
{
	char	**env;
	char	**new_arr;
	char	**vars;
	int		i;

	env = main_struct.s_env->env_arr;
	vars = main_struct.args;
	i = 0;
	while (args[i])
		env = add_vars(env, args[i++], vars);
	new_arr = copy_env(env);
	print_export(sort_export(new_arr));
	write(1,"\n",1);
	// print_export(env);
	free_arr(new_arr);
}