/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvinnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 11:11:20 by rvinnie           #+#    #+#             */
/*   Updated: 2021/04/16 11:11:22 by rvinnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_all *main_struct, char **arr)
{
	int		i;
	int		flag_n;

	main_struct->state = 0;
	i = 1;
	if (arr[i] && ft_strncmp(arr[i], "-n", 3) == 0)
	{
		flag_n = 1;
		i++;
	}
	else
		flag_n = 0;
	while (arr[i])
	{
		write(1, arr[i], ft_strlen(arr[i]));
		i++;
		if (arr[i])
			write(1, " ", 1);
	}
	if (!flag_n)
		write(1, "\n", 1);
}
