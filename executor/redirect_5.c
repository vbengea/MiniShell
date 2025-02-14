/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/07 03:11:13 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

t_redirection	*redlist_new(void *content)
{
	t_redirection	*lst;

	lst = malloc(sizeof(t_redirection));
	if (lst)
	{
		lst->file = content;
		lst->next = NULL;
	}
	return (lst);
}

void	redlist_add(t_redirection **lst, t_redirection *new)
{
	t_redirection	*tmp;

	tmp = *lst;
	*lst = new;
	(*lst)->next = tmp;
}

void	redlist_iter(t_redirection *lst, void (*f)(void *, int x))
{
	while (lst)
	{
		(*f)(lst->file, lst->is_quote);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}

t_redirection	*ft_lstred(t_redirection *node)
{
	t_redirection	*lst;

	lst = malloc(sizeof(t_redirection));
	if (lst)
	{
		lst->file = node->file;
		lst->type = node->type;
		lst->otype = node->otype;
		lst->next = NULL;
	}
	return (lst);
}

void	print_redirs(void *content, int flag)
{
	char *str;

	str = (char *) content;
	printf("(%s [%d]) ", str, flag);
}
