/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:09:03 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/07 18:46:45 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				a;
	unsigned char		*ndst;
	unsigned const char	*nsrc;

	a = 0;
	ndst = dst;
	nsrc = src;
	while (a < n)
	{
		if (nsrc[a] == (unsigned char)c)
		{
			ndst[a] = nsrc[a];
			return (&(ndst[a + 1]));
		}
		ndst[a] = nsrc[a];
		a++;
	}
	return (NULL);
}
