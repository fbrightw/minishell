/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:45:06 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/10 16:35:31 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_quantity(int new, int *k)
{
	while (new / 10 != 0)
	{
		new /= 10;
		*k += 1;
	}
	*k += 1;
}

static	int		ft_is_negative(int *n, int *k, int *fl)
{
	if (*n < 0 && *n != -2147483648)
	{
		*n *= -1;
		*k = 1;
		*fl = 1;
	}
	if (*n == -2147483648)
	{
		*k = 2;
		*fl = 2;
		*n = 214748364;
	}
	return (*n);
}

static	void	ft_record(int new, int k, int fl, char *s)
{
	while (k > 0)
	{
		k -= 1;
		if (k == 0 && (fl == 2 || fl == 1))
			s[k] = '-';
		else
			s[k] = new % 10 + '0';
		new /= 10;
	}
}

char			*ft_itoa(int n)
{
	int		fl;
	int		new;
	char	*s;
	int		k;

	fl = 0;
	k = 0;
	new = 0;
	ft_is_negative(&n, &k, &fl);
	new = n;
	ft_quantity(new, &k);
	s = (char*)malloc((k + 1) * sizeof(char));
	if (!s)
		return (0);
	s[k] = '\0';
	if (fl == 2)
	{
		k -= 1;
		s[k] = 8 + '0';
	}
	ft_record(new, k, fl, s);
	return (s);
}
