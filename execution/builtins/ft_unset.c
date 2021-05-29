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

char	**reconstruct_arr(t_all *main_struct, char **env_arr, char *arg)
{
	int		i;
	int		j;
	char	**new_arr;

	i = 0;
	j = 0;
	while (env_arr[i])
		i++;
	new_arr = malloc(i * sizeof(char*));
	if (!new_arr)
	{
		error_msg("failed to allocate memory", 0, main_struct, 1);
		free_arr(env_arr);
		exit(1); // replace with your function
	}
	i = 0;
	while (env_arr[j])
	{
		if (ft_strncmp(env_arr[j], arg, ft_strlen(arg)) == 0 &&
						(env_arr[j][ft_strlen(arg)] == '=' ||
						env_arr[j][ft_strlen(arg)] == '\0'))
		{
			j++;
			continue ;
		}
		new_arr[i] = env_arr[j];
		j++;
		i++;
	}
	free(env_arr);
	new_arr[i] = NULL;
	return (new_arr);
}

void	ft_unset(t_all *main_struct, char **arr)
{
	int		len;
	int		i;
	int		j;
	char	**env_arr;

	main_struct->state = 0;
	i = 1;
	env_arr = main_struct->envs->env_arr;
	while (arr[i])
	{
		j = 0;
		len = ft_strlen(arr[i]);
		if (check_identifier(arr[i], 0) == -1)
		{
			error_msg("not a valid identifier", 0, main_struct, 1);
			i++;
			continue ;
		}
		while (env_arr[j])
		{
			if (ft_strncmp(env_arr[j], arr[i], ft_strlen(arr[i])) == 0 &&
							(env_arr[j][ft_strlen(arr[i])] == '=' ||
							env_arr[j][ft_strlen(arr[i])] == '\0'))
				env_arr = reconstruct_arr(main_struct, env_arr, arr[i]);
			j++;
		}
		i++;
	}
	main_struct->envs->env_arr = env_arr;
}