/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juandanielflores <juandanielflores@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:14:43 by juandanielf       #+#    #+#             */
/*   Updated: 2024/09/23 01:59:08 by juandanielf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->content);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}
