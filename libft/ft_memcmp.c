/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:07:00 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/07 18:51:23 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t					i;
	unsigned char const		*nstr1;
	unsigned char const		*nstr2;

	i = 0;
	nstr1 = str1;
	nstr2 = str2;
	while (i < n)
	{
		if (nstr1[i] == nstr2[i])
			i++;
		else
			return (nstr1[i] - nstr2[i]);
	}
	return (0);
}
