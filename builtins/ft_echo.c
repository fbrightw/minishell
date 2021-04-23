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

#include "../includes/minishell.h"

int		check_args(t_all main_struct, char *str)
{
	char	**args;
	int		len;
	int		flag;
	int		j;

	flag = 0;
	args = main_struct.args;
	j = 0;
	while (args[j])
	{
		len = ft_strlen(str);
		if ((ft_strncmp(args[j], str, len)) == 0 &&
			args[j][len] == '=')
		{
			write(1, args[j] + len + 1, ft_strlen(args[j] + len + 1));
			flag = 1;
			break ;
		}
		j++;
	}
	return (flag);
}

int		check_env(t_all main_struct, char *str)
{
	char	**env;
	int		len;
	int		flag;
	int		j;

	flag = 0;
	env = main_struct.s_env->env_arr;
	j = 0;
	while (env[j])
	{
		len = ft_strlen(str);
		if ((ft_strncmp(env[j], str, len)) == 0 &&
			env[j][len] == '=')
		{
			write(1, env[j] + len + 1, ft_strlen(env[j] + len + 1));
			flag = 1;
			break ;
		}
		j++;
	}
	return (flag);
}

int		handle_dollar(t_all main_struct, char *str)
{
	
	int		i;
	int		flag;

	i = 1;
	while (str[i] == '$')
	{
		write(1, "$", 1);
		i++;
	}
	flag = check_args(main_struct, str + i);
	if (!flag)
		flag = check_env(main_struct, str + i);
	return (flag);
}

void	ft_echo(t_all main_struct, char **to_print, int flag_n)
{
	int		i;
	int		flag;

	i = 0;
	while (to_print[i])
	{
		flag = 1;
		if (to_print[i][0] == '$')
			flag = handle_dollar(main_struct, to_print[i]);
		else
			write(1, to_print[i], ft_strlen(to_print[i]));
		i++;
		if (to_print[i] && flag == 1)
			write(1," ",1);
	}
	if (!flag_n)
		write(1, "\n", 1);
}
