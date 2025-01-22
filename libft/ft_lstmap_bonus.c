/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:14:58 by juandanielf       #+#    #+#             */
/*   Updated: 2024/09/28 15:14:50 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	t_list	*get_list(t_list *lst, void *(*f)(void *))
{
	t_list	*list;

	list = NULL;
	if (lst)
		list = ft_lstnew((*f)(lst->content));
	return (list);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		size;
	int		i;
	t_list	*list;
	t_list	*first;

	size = ft_lstsize(lst);
	list = get_list(lst, f);
	first = list;
	if (list)
	{
		lst = lst->next;
		i = 1;
		while (lst != NULL && i++ < size)
		{
			list->next = ft_lstnew((*f)(lst->content));
			if (list->next == NULL)
			{
				ft_lstclear(&first, del);
				return (first);
			}
			lst = lst->next;
			list = list->next;
		}
	}
	return (first);
}
