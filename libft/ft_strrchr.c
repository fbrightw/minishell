/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:18:32 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/07 19:28:08 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const void *str, int ch)
{
	int i;

	i = ft_strlen(str);
	while (i > 0 && *(char*)(str + i) != ch)
		i--;
	if (*(char*)(str + i) == ch)
		return (void*)(str + i);
	return (0);
}
