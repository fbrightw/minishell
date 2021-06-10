/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvinnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:33:48 by rvinnie           #+#    #+#             */
/*   Updated: 2021/06/08 17:33:49 by rvinnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_all *main_struct, char **arr)
{
	int	arr_len;

	arr_len = get_arr_len(arr);
	if (arr_len == 1)
		exit(main_struct->state);
	if (!ft_isnum(arr[1]))
	{
		error_msg("numeric argument required", 0, main_struct, 2);
		free_variables(main_struct);
		exit(2);
	}
	if (arr_len > 2)
	{
		error_msg("too many arguments", 0, main_struct, 1);
		exit(1);
	}
	exit(ft_atoi(arr[1]) % 256);
	return (0);
}
