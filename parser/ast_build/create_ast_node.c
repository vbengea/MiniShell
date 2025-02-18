/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:15:50 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/18 22:38:37 by jflores          ###   ########.fr       */
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
	node->discovered = 0;
	node->traversed = 0;
	node->exit = -1;
	node->in_fd = -1;
	node->out_fd = -1;
	node->has_group_in_fd = 0;
	node->has_group_out_fd = 0;
	node->parent = NULL;
	node->redirs = NULL;
	node->has_env = false;
	node->env_declare = false;
	ft_memset((void *)node->expand_flag, 0, 200);
	ft_memset((void *)node->has_space, 0, 200);
	node->args_index = 0;
	node->path = NULL;
	return (node);
}
