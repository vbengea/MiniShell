/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:15:50 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/07 19:59:48 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node *create_ast_node(t_node_type type, char **cmd_args)
{
	t_ast_node *node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = cmd_args;
	node->redirs = NULL;
	node->left = NULL;
	node->right = NULL;
	node->side = 0;
	node->parent = NULL;
	node->exit = -1;
	node->fd = -1;
	return (node);
}