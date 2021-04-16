/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:43:02 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/07 19:07:55 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const void *str, int ch)
{
	int i;

	i = 0;
	while (*(char*)(str + i) != ch && *(char*)(str + i) != 0)
		i++;
	if (*(char*)(str + i) == ch)
		return (char*)(str + i);
	return (0);
}
