/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvinnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:30:02 by rvinnie           #+#    #+#             */
/*   Updated: 2021/06/08 17:30:03 by rvinnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_msg(char *str, int is_errno, t_all *main_struct, int new_state)
{
	main_struct->state = new_state;
	write(2, "error: ", 8);
	if (is_errno)
		write(2, strerror(is_errno), ft_strlen(strerror(is_errno)));
	else if (str)
		write(2, str, ft_strlen(str));
	else
		write(2, "undefined error", 16);
	write(2, "\n", 1);
}
