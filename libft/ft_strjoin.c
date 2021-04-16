/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 13:13:55 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/10 17:15:48 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		k;
	char	*nstr;

	i = 0;
	k = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	if (!(nstr = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	while (s1[i] != '\0')
	{
		*(char*)(nstr + i) = s1[i];
		i++;
	}
	k = i;
	i = 0;
	while (s2[i] != '\0')
	{
		*(char*)(nstr + k) = s2[i];
		i++;
		k++;
	}
	nstr[k] = '\0';
	return (nstr);
}
