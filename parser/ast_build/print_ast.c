/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:48:17 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/08 11:12:09 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

void print_ast(t_ast_node *node, int level)
{
	if (!node)
		return;

	for (int i = 0; i < level; i++)
		printf("  ");

	printf("Node type: %d", node->type);
	printf(", SIDE: %d", node->side);

	if (node->type == NODE_CMND && node->args)
	{
		printf(", args: ");
		for (int j = 0; node->args[j] != NULL; j++)
		{
			printf("%s ", node->args[j]);
		}
	}
	// printf("Node args pointer: %p", node->args);
	if ((node->type == NODE_CMND || node->type == NODE_GROUP) && node->redirs)
	{
		t_redirection *redir = node->redirs;
		while (redir)
		{
			printf(", Redirect type: %d, File: %s", redir->type, redir->file);
			redir = redir->next;
		}
	}
	if (node->parent)
		printf(", Parent type: %d", node->parent->type);

	if (node->nid)
		printf(", Node id: %d", node->nid);
	printf("\n");

	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}
