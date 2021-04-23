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

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	size_t	size;
	char	buf[PATH_MAX];
	char	*ptr;

	ptr = getcwd(buf, PATH_MAX);				// don't forget error checker and errno and ptr == NULL
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
}
