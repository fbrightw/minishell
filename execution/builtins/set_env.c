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

void	put_error_exit(t_all *main_struct, char *err)
{
	error_msg(err, 0, main_struct, 1);
	exit(1);
}

void	set_env(t_all *main_struct, t_env *s_env, char **env)
{
	int		row;
	int		i;
	char	**env_array;

	row = 0;
	i = 0;
	while (env[row])
		row++;
	env_array = malloc((row + 1) * sizeof(char *));
	if (!env_array)
		put_error_exit(main_struct, "failed to allocate memory");
	while (env[i])
	{
		env_array[i] = ft_strdup(env[i]);
		if (!env_array[i++])
		{
			free_arr(env_array);
			put_error_exit(main_struct, "failed to allocate memory");
		}
	}
	env_array[i] = NULL;
	s_env->env_arr = env_array;
	s_env->home = getenv("HOME");
	if (!s_env->home)
		put_error_exit(main_struct, "failed to get environment variable");
}
