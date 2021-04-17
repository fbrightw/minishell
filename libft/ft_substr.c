/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:47:39 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/11 13:18:13 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	char const	*news;
	size_t		i;

	news = s;
	substr = NULL;
	substr = (char*)ft_calloc((len + 1), sizeof(char));
	i = 0;
	if (!news || !substr)
		return (NULL);
	len = len + start;
	if (start > ft_strlen(s))
		return (substr);
	while (start < len && news)
	{
		substr[i] = news[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
