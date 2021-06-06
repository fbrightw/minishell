#include "../../includes/minishell.h"

int		check_identifier(char *arg, int is_export)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_' && !is_export)
			return (-1);
		if (ft_isalnum(arg[i]) == 0 && is_export && arg[i] != '=')
			return (-1);
		i++;
	}
	if ((arg[0] >= 'a' && arg[0] <= 'z') ||
		(arg[0] >= 'A' && arg[0] <= 'Z') || arg[0] == '_')
		return (1);
	return (-1);
}

void	print_export(char **env)
{
	int		i;
	int		len;

	len = get_arr_len(env);
	i = 1;
	while (env[i])
	{
		write(1, "declare -x ", 12);
		print_with_quotes(env[i]);
		if (i == len - 1)
			break ;
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
			if (ft_strncmp_export(env[j], env[j + 1], ft_strlen(env[j])) > 0)
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

char	**copy_env(t_all *main_struct, char **env)
{
	char	**new_arr;
	int		row;
	int		i;

	row = get_arr_len(env);
	new_arr = malloc((row + 1) * sizeof(char*));
	if (!new_arr)
	{
		error_msg("failed to allocate memory", 0, main_struct, 1);
		exit(1); // replace with your function
	}
	i = 0;
	while (env[i])
	{
		new_arr[i] = ft_strdup(env[i]);
		if (!new_arr[i])
		{
			error_msg("failed to allocate memory", 0, main_struct, 1);
			free_arr(new_arr);
			exit(1); // replace with your function
		}
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

void	ft_export(t_all *main_struct, char **arr)
{
	char	**env;
	char	**new_arr;
	char	*vars[1];
	int		i;

	main_struct->state = 0;
	env = main_struct->envs->env_arr;
	// vars = main_struct->vars;
	vars[0] = NULL;
	i = 1;
	while (arr[i])
	{
		if (check_identifier(arr[i], 1) == -1)
			error_msg("not a valid identifier", 0, main_struct, 1);
		else
			env = add_vars(main_struct, env, arr[i], vars);
		i++;
	}
	main_struct->envs->env_arr = env;
	new_arr = copy_env(main_struct, env);
	if (get_arr_len(arr) == 1)
	{
		print_export(sort_export(new_arr));
		write(1,"\n",1);
	}
	free_arr(new_arr);
}