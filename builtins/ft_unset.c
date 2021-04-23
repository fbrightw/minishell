/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvinnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:57:28 by rvinnie           #+#    #+#             */
/*   Updated: 2021/04/17 14:57:29 by rvinnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**reconstruct_arr(char **env_arr, char *arg)
{
	int		i;
	int		j;
	char	**new_arr;

	i = 0;
	j = 0;
	while (env_arr[i])
		i++;
	new_arr = malloc(i * sizeof(char*));
	i = 0;
	while (env_arr[j])
	{
		if (ft_strncmp(env_arr[j], arg, ft_strlen(arg)) == 0 &&
						env_arr[j][ft_strlen(arg)] == '=')
		{
			free(env_arr[j++]);
			continue ;
		}
		new_arr[i] = ft_strdup(env_arr[j]);
		free(env_arr[j++]);
		i++;
	}
	free(env_arr);
	new_arr[i] = NULL;
	return (new_arr);
}

void	ft_unset(t_env  *s_env, char **arr)
{
	int		len;
	int		i;
	int		j;
	char	**env_arr;

	i = 1;
	env_arr = s_env->env_arr;
	while (arr[i])
	{
		j = 0;
		len = ft_strlen(arr[i]);
		while (env_arr[j])
		{
			if (ft_strncmp(env_arr[j], arr[i], ft_strlen(arr[i])) == 0 &&
							env_arr[j][ft_strlen(arr[i])] == '=')
				env_arr = reconstruct_arr(env_arr, arr[i]);
			j++;
		}
		i++;
	}
	s_env->env_arr = env_arr;
}