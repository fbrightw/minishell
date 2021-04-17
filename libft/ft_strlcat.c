/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:48:19 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/07 19:16:54 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t		i;
	size_t		dlen;
	char		*ndst;
	const char	*nsrc;

	i = 0;
	ndst = dst;
	nsrc = src;
	dlen = ft_strlen(dst);
	if (nsrc[i] == 0)
		return (dlen);
	if (dlen < n)
	{
		while (i < (n - dlen - 1) && nsrc[i])
		{
			ndst[i + dlen] = nsrc[i];
			i++;
		}
	}
	else
		return (ft_strlen((char*)src) + n);
	ndst[i + dlen] = '\0';
	return (ft_strlen((char*)src) + dlen);
}
