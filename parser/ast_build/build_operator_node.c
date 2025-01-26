/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_operator_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:49:48 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/26 11:55:49 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node	*build_operator_node(t_token *split_point, \
				t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*root;

	if (split_point->type == TOKEN_PIPE)
		root = create_ast_node(NODE_PIPE, NULL);
	else if (split_point->type == TOKEN_AND)
		root = create_ast_node(NODE_AND, NULL);
	else if (split_point->type == TOKEN_OR)
		root = create_ast_node(NODE_OR, NULL);
	else if (split_point->type == TOKEN_REDIRECT_IN
		|| split_point->type == TOKEN_REDIRECT_OUT
		|| split_point->type == TOKEN_APPEND)
		root = create_redirect_node(split_point);
	else
		return (NULL);
	root->left = left;
	root->right = right;
	return (root);
}
