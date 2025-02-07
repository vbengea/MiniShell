/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_operator_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:49:48 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/07 13:10:31 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node *build_operator_node(t_ast_node *left, t_token *split_point)
{
	t_ast_node *right;
	t_ast_node *root;

	root = NULL;
	right = NULL;

	if (split_point->type == TOKEN_PIPE)
		root = create_ast_node(NODE_PIPE, NULL);
	else if (split_point->type == TOKEN_AND)
		root = create_ast_node(NODE_AND, NULL);
	else if (split_point->type == TOKEN_OR)
		root = create_ast_node(NODE_OR, NULL);

	if (split_point->next)
		right = build_ast(split_point->next);

	if (root)
	{
		root->left = left;
		root->right = right;

		// Set parent pointers
		if (root->left)
		{
			root->left->side = 0;
			root->left->parent = root;
		}
		if (root->right)
		{
			root->right->side = 1;
			root->right->parent = root;
		}
	}

	return (root);
}