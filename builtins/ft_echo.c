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

#include "builtins.h"

// flag_n == 0 -> with    "\n"
// flag_n == 1 -> without "\n"
// No errors in function

void	ft_echo(char *str, int flag_n)
{
	write(1, str, strlen(str)); // change to ft_strlen
	if (!flag_n)
		write(1, "\n", 1);
}