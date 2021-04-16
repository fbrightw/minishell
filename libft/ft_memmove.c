/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 19:00:30 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/07 19:02:39 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*ndst;
	unsigned const char	*nsrc;
	size_t				c;

	ndst = dst;
	nsrc = src;
	c = 0;
	if (src == dst)
		return (dst);
	else if (src > dst)
		while (c < n)
		{
			ndst[c] = nsrc[c];
			c++;
		}
	else
	{
		c = n;
		while (c > 0)
		{
			c--;
			ndst[c] = nsrc[c];
		}
	}
	return (dst);
}
