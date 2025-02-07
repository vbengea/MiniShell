/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:48:17 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/07 13:04:52 by vbengea          ###   ########.fr       */
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

	if (node->args)
	{
		printf(", args: ");
		for (int j = 0; node->args[j] != NULL; j++)
		{
			printf("%s ", node->args[j]);
		}
	}

	if (node->type == NODE_CMND && node->redirs)
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

	printf("\n");

	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}