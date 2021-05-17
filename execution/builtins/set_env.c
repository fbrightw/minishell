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

#include "builtins.h"

void	set_env(t_env *s_env, char **env)
{
	int		row;
	int		i;
	char	**env_array;

	row = 0;
	i = 0;
	while (env[row])
		row++;
	env_array = malloc((row + 1) * sizeof(char*));
	while (env[i])
	{
		env_array[i] = ft_strdup(env[i]);
		i++;
	}
	env_array[i] = 0;
	s_env->env_arr = env_array;
	i = 0;
	s_env->home = getenv("HOME");
}
