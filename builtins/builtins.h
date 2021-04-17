/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvinnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 11:11:29 by rvinnie           #+#    #+#             */
/*   Updated: 2021/04/16 11:11:30 by rvinnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

typedef struct
{
	char	*home;
}			t_env;

// Main builtins functions
void	ft_echo(char *str, int flag_n);
void	ft_pwd(void);
void	ft_env(char *env[]);
void	ft_cd(t_env *s_env, char *arg);

// Builtins utils
int		get_arr_len(char *arr[]);
void	ft_putstr_n(char *str);
char	*ft_strcat(char *s1, char *s2);
size_t	ft_strlen(const char *s);

#endif
