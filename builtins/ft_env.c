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

#include "builtins.h"

void	ft_env(char *env[])
{
	int		i;
	char	*current_var;

	i = 0;
	while (env[i])
	{
		current_var = env[i];
		ft_putstr_n(current_var);
		i++;
	}
}
