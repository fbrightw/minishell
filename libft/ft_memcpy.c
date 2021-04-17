/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:09:03 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/07 18:54:27 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t a;

	a = 0;
	if (dst == NULL && src == NULL)
		return (dst);
	while (a < n)
	{
		*(char*)(dst + a) = *(char*)(src + a);
		a++;
	}
	return (dst);
}
