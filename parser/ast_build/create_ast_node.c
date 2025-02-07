/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:15:50 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/07 03:13:06 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node	*create_ast_node(t_node_type type, char **cmd_args)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	ft_bzero(node, sizeof(node));
	node->type = type;
	node->args = cmd_args;
	node->file = NULL;
	node->redirect_type = REDIRECT_NONE;
	node->left = NULL;
	node->right = NULL;
	node->nid = 0;
	node->side = 0;
	node->exit = 0;
	node->fd = -1;
	node->parent = NULL;
	node->redirs = NULL;
	return (node);
}
