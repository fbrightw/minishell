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

#include "../../includes/minishell.h"

void	reconstruct_arr2(char **env_arr, char **new_arr, char *arg)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (env_arr[j])
	{
		if (ft_strncmp(env_arr[j], arg, ft_strlen(arg)) == 0
			&& (env_arr[j][ft_strlen(arg)] == '='
			|| env_arr[j][ft_strlen(arg)] == '\0'))
		{
			j++;
			continue ;
		}
		new_arr[i] = env_arr[j];
		j++;
		i++;
	}
	new_arr[i] = NULL;
}

char	**reconstruct_arr(t_all *main_struct, char **env_arr, char *arg)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (env_arr[i])
		i++;
	new_arr = malloc(i * sizeof(char *));
	if (!new_arr)
	{
		error_msg("failed to allocate memory", 0, main_struct, 1);
		free_arr(env_arr);
		exit(1); // replace with your function
	}
	reconstruct_arr2(env_arr, new_arr, arg);
	free(env_arr);
	return (new_arr);
}

char	**check_envs(t_all *main_struct, char **arr, char	**env_arr, int i)
{
	int		j;
	int		len;

	len = ft_strlen(arr[i]);
	j = 0;
	while (env_arr[j])
	{
		if (ft_strncmp(env_arr[j], arr[i], len) == 0
			&& (env_arr[j][len] == '=' || env_arr[j][len] == '\0'))
			env_arr = reconstruct_arr(main_struct, env_arr, arr[i]);
		j++;
	}
	return (env_arr);
}

void	ft_unset(t_all *main_struct, char **arr)
{
	int		len;
	int		i;
	char	**env_arr;

	main_struct->state = 0;
	i = 1;
	env_arr = main_struct->envs->env_arr;
	while (arr[i])
	{
		len = ft_strlen(arr[i]);
		if (check_identifier(arr[i], 0) == -1)
		{
			error_msg("not a valid identifier", 0, main_struct, 1);
			i++;
			continue ;
		}
		env_arr = check_envs(main_struct, arr, env_arr, i);
		i++;
	}
	main_struct->envs->env_arr = env_arr;
}
