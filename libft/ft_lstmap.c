/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrightw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:20:06 by fbrightw          #+#    #+#             */
/*   Updated: 2020/11/11 18:06:24 by fbrightw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*new_list;
	void	*content;
	t_list	*element;

	new_list = 0;
	while (lst)
	{
		content = (*f)(lst->content);
		element = 0;
		if (content)
			element = ft_lstnew(content);
		if (element)
			ft_lstadd_back(&new_list, element);
		else
			ft_lstclear(&new_list, del);
		lst = lst->next;
	}
	return (new_list);
}
