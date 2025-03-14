/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:49:12 by jflores           #+#    #+#             */
/*   Updated: 2025/03/04 19:08:13 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	is_pipe_state(t_ast_node *node)
{
	if (node->parent && node->parent->type == NODE_PIPE)
		return (1);
	return (0);
}

int	is_identifier(char c)
{
	if (c && c != 39 && (ft_isalnum(c) || c == '_' || c == '?'))
		return (1);
	else
		return (0);
}

void	print_redirs(void *content, int flag)
{
	char	*str;

	str = (char *) content;
	printf("(%s [%d]) ", str, flag);
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
