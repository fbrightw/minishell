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

void	ft_cd(t_all *main_struct, char **arr)
{
	int		ret;
	int		len;
	char	*new_dir;
	char	*arg;

	main_struct->state = 0;
	len = get_arr_len(arr);
	if (len == 1)
		new_dir = ft_strdup(main_struct->envs->home);
	else if (len > 2)
	{
		error_msg("too many arguments", 0, main_struct, 1);
		return ;
	}
	else
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
	free(new_dir);
}
