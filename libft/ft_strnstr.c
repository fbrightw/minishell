/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 12:04:51 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/10 16:18:00 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_algorithm(const char *dst, const char *src, size_t n)
{
	size_t	i1;
	size_t	i2;
	int		k;

	i1 = 0;
	i2 = 0;
	k = 0;
	while (dst[i1] != '\0' && i1 < n)
	{
		if (dst[i1] == src[i2] && i1 < n)
		{
			k = i1;
			while (dst[i1] == src[i2] && i1 < n && src[i2])
			{
				i2++;
				i1++;
			}
			if (!src[i2])
				return (char*)(dst + i1 - i2);
			(dst[i1] ? (i1 = k) : i1--);
			i2 = 0;
		}
		i1++;
	}
	return (0);
}

char	*ft_strnstr(const char *dst, const char *src, size_t n)
{
	if (ft_strlen(src) == 0)
		return (char*)dst;
	return (ft_algorithm(dst, src, n));
}
