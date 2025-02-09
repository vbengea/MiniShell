/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:15:50 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/09 12:11:35 by vbengea          ###   ########.fr       */
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
	node->left = NULL;
	node->right = NULL;
	node->nid = 0;
	node->side = 0;
	node->exit = 0;
	node->in_fd = -1;
	node->out_fd = -1;
	node->has_group_in_fd = 0;
	node->has_group_out_fd = 0;
	node->parent = NULL;
	node->redirs = NULL;
	node->has_env = false;
	node->env_declare = false;
	return (node);
}
