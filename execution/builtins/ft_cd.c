/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvinnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:53:41 by rvinnie           #+#    #+#             */
/*   Updated: 2021/04/17 11:53:42 by rvinnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_pwd_env(t_all *main_struct)
{
	char	*new_dir;
	char	buf[PATH_MAX];
	char	**env_arr;
	int		i;

	new_dir = getcwd(buf, PATH_MAX);
	if (new_dir == NULL)
	{
		error_msg(NULL, errno, main_struct, 1);
		return ;
	}
	env_arr = main_struct->envs->env_arr;
	i = 0;
	while (env_arr[i])
	{
		if ((ft_strncmp(env_arr[i], "PWD", 3) == 0)
			&& (env_arr[i][3] == '='))
		{
			free(env_arr[i]);
			env_arr[i] = ft_strcat("PWD=", new_dir);
			break ;
		}
		i++;
	}
}

char	*get_home_directory(t_all *main_struct, char **arr)
{
	int		len;
	char	*new_dir;

	new_dir = NULL;
	len = get_arr_len(arr);
	if (len == 1)
		new_dir = ft_strdup(main_struct->envs->home);
	else if (len > 2)
		new_dir =ft_strdup(arr[1]);
	return (new_dir);
}

void	ft_cd(t_all *main_struct, char **arr)
{
	int		ret;
	char	*new_dir;
	char	*arg;

	main_struct->state = 0;
	new_dir = get_home_directory(main_struct, arr);
	if (get_arr_len(arr) == 2)
	{
		arg = arr[1];
		if (arg[0] == '~')
			new_dir = ft_strcat(main_struct->envs->home, ++arg);
		else
			new_dir = ft_strdup(arg);
	}
	if (!new_dir)
	{
		error_msg("failed to allocate memory", 0, main_struct, 1);
		exit(1); // replace with your function
	}
	ret = chdir(new_dir);
	if (ret == -1)
		error_msg(NULL, errno, main_struct, 1);
	else
		set_pwd_env(main_struct);
	free(new_dir);
}
