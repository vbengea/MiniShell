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

void	ft_rediter(t_redirection *lst, void (*f)(t_redirection *))
{
	while (lst)
	{
		(*f)(lst);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}

int	has_group_redirection(t_ast_node *ast, int is_infile)
{
	t_ast_node	*node;

	node = ast;
	while (ast)
	{
		if (ast->parent == NULL)
			break ;
		ast = ast->parent;
		if (ast->type == NODE_GROUP && ast->redirs)
		{
			if (is_infile)
			{
				if (ast->in_fd >= 0)
				{
					node->in_fd = ast->in_fd;
					node->has_group_in_fd = 1;
					return (1);
				}
			}
			else
			{
				if (ast->out_fd >= 0)
				{
					node->out_fd = ast->out_fd;
					node->has_group_out_fd = 1;
					return (1);
				}
			}
		}
	}
	return (0);
}
