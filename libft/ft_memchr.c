/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:54:24 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/07 18:50:10 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *dst, int c, size_t n)
{
	size_t					a;
	unsigned const char		*newdst;

	a = 0;
	newdst = dst;
	while (a < n)
	{
		if (newdst[a] == (unsigned char)c)
			return (void*)(dst + a);
		a++;
	}
	return (NULL);
}
