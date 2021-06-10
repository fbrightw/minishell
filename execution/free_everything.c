#include "../includes/minishell.h"

void	free_variables(t_all *main_struct)
{
	int	i;

	i = 0;
	while (main_struct->envs->env_arr[i])
	{
		free(main_struct->envs->env_arr[i]);
		i++;
	}
	free(main_struct->envs);
	free(main_struct);
}

void	free_processes(t_var *var)
{
	int	i;

	i = 0;
	free(var->processes);
	while (var->pipes[i])
	{
		if (var->pipes[i])
			free(var->pipes[i]);
		i++;
	}
	free(var->pipes);
}
