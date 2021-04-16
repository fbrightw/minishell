/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:02:34 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/07 19:10:06 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	size;
	size_t	i;

	size = ft_strlen(s1);
	copy = (char*)malloc((size + 1) * sizeof(char));
	i = 0;
	if (copy == NULL)
		return (NULL);
	while (i < size)
	{
		copy[i] = *(char*)(s1 + i);
		i++;
	}
	copy[i] = 0;
	return (copy);
}
