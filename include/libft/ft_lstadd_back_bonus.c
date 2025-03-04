/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juandanielflores <juandanielflores@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:13:51 by juandanielf       #+#    #+#             */
/*   Updated: 2024/09/23 01:58:53 by juandanielf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp == NULL)
		*lst = new;
	else
	{
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				tmp->next = new;
				break ;
			}
			tmp = tmp->next;
		}
	}
}
