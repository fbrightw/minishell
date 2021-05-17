/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvinnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:44:13 by rvinnie           #+#    #+#             */
/*   Updated: 2021/04/17 11:44:14 by rvinnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int get_arr_len(char *arr[])
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_putstr_n(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

char	*ft_strcat(char *s1, char *s2)
{
	char	*ret;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc(size + 1);
	if (ret == NULL)
		return (NULL);
	while (s1[i])
		ret[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}