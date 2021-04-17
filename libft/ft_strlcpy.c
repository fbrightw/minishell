/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:48:19 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/07 19:19:40 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t		i;
	char		*ndest;
	const char	*nsrc;

	i = 0;
	ndest = dest;
	nsrc = src;
	if (!ndest || !nsrc)
		return (0);
	if (dstsize > 1)
	{
		while (i < dstsize - 1 && nsrc[i])
		{
			ndest[i] = nsrc[i];
			i++;
		}
		ndest[i] = 0;
	}
	return (ft_strlen(nsrc));
}
