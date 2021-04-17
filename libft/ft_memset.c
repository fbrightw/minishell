/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:29:01 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/07 19:04:03 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int a, size_t n)
{
	size_t c;

	c = 0;
	while (c < n)
	{
		*(unsigned char*)(dst + c) = (unsigned char)(a);
		c++;
	}
	return (dst);
}
