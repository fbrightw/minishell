/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvinnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 12:22:46 by rvinnie           #+#    #+#             */
/*   Updated: 2021/04/16 12:22:47 by rvinnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// env -> environment variables
// No errors in function

void	ft_pwd(char	*env[])
{
	int		i;
	char	*current_var;

	i = 0;
	while (env[i])
	{
		current_var = env[i];
		if (strncmp(current_var, "PWD", 3) == 0) 				//ft_strncmp
			write(1, current_var + 4, strlen(current_var) - 4);
		i++;
	}
	write(1, "\n", 1);
}
