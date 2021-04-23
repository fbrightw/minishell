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

#include "../includes/minishell.h"

void	ft_cd(t_env *s_env, char *arg)
{
	int		ret;
	char	*new_dir;

	if (arg[0] == '\0')
		new_dir = ft_strdup(s_env->home);
	else if (arg[0] == '~')
		new_dir = ft_strcat(s_env->home, ++arg);
	else
		new_dir = ft_strdup(arg);
	ret = chdir(new_dir);	// don't forget error checker
	free(new_dir);
}