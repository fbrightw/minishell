/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvinnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 13:54:17 by rvinnie           #+#    #+#             */
/*   Updated: 2021/04/17 13:54:18 by rvinnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_env(t_all *main_struct, t_env *s_env, char **env)
{
	int		row;
	int		i;
	char	**env_array;

	row = 0;
	i = 0;
	while (env[row])
		row++;
	env_array = malloc((row + 1) * sizeof(char*));
	if (!env_array)
	{
		error_msg("failed to allocate memory", 0, main_struct, 1);
		exit(1);
	}
	while (env[i])
	{
		env_array[i] = ft_strdup(env[i]);
		if (!env_array[i])
		{
			error_msg("failed to allocate memory", 0, main_struct, 1);
			free_arr(env_array);
			exit(1);
		}
		i++;
	}
	env_array[i] = NULL;
	s_env->env_arr = env_array;
	i = 0;
	s_env->home = getenv("HOME");
	if (!s_env->home)
	{
		error_msg("failed to get environment variable", 0, main_struct, 1);
		exit(1);
	}
}
