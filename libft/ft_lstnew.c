/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:05:21 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/11 11:02:28 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *name;

	name = malloc(sizeof(t_list));
	if (name == 0)
		return (0);
	name->content = content;
	name->next = 0;
	return (name);
}
