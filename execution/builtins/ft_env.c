/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvinnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:50:56 by rvinnie           #+#    #+#             */
/*   Updated: 2021/04/16 13:50:57 by rvinnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_equal_sign(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_env(t_all *main_struct, char **arr)
{
	int		i;
	char	**env;

	main_struct->state = 0;
	if (get_arr_len(arr) > 1)
	{
		error_msg("too many arguments", 0, main_struct, 1);
		return ;
	}
	i = 0;
	env = main_struct->envs->env_arr;
	while (env[i])
	{
		if (check_equal_sign(env[i]) == 1)
		{
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}
