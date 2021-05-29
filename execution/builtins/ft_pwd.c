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

#include "../../includes/minishell.h"

void	ft_pwd(t_all *main_struct, char **arr)
{
	size_t	size;
	char	buf[PATH_MAX];
	char	*ptr;

	main_struct->state = 0;
	ptr = getcwd(buf, PATH_MAX);
	if (ptr == NULL)
	{
		error_msg(NULL, errno, main_struct, 1);
		return ;
	}
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
}
