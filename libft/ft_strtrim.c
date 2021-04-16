/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:49:01 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/13 13:57:42 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_find_first_index(char const *s1, char const *set, int i)
{
	size_t k;

	k = 0;
	while (s1[i])
	{
		while (s1[i] != set[k] && set[k])
			k++;
		if (s1[i] == set[k] && s1[i])
		{
			k = 0;
			i++;
		}
		else
			return (i);
	}
	return (i);
}

int		ft_find_last_index(char const *s1, char const *set, int i, int first)
{
	size_t k;

	k = 0;
	while (i >= first)
	{
		while (s1[i] == set[k] && i >= first && set[k])
		{
			i--;
			k = 0;
		}
		if (s1[i] != set[k] && set[k])
			k++;
		else
			return (i);
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*arr;
	int		i;
	int		first;
	int		last;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	first = ft_find_first_index(s1, set, i);
	last = ft_find_last_index(s1, set, ft_strlen(s1) - 1, first);
	arr = ft_calloc((last - first + 2), sizeof(char));
	if (arr == NULL)
		return (0);
	i = 0;
	while (first <= last)
	{
		arr[i] = s1[first];
		i++;
		first++;
	}
	arr[i] = '\0';
	return (char*)arr;
}
