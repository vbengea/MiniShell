/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 09:19:13 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/23 09:32:47 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data_structure.h"
#include <stdio.h>

void	print_ast(t_ast_node *node, int indent)
{
	int	i;

	if (!node)
		return ;

	print_ast(node->right, indent + 4);
	i = 0;
	while (i < indent)
	{
		printf(" ");
		i++;
	}

	if (node->type == NODE_REDIRECT)
	{
		if (node->redirect_type == 1)
			printf(">\n");
		else if (node->redirect_type == 2)
			printf("<\n");
	}
	if (node->type == NODE_PIPE)
		printf("|\n");
	if (node->type == NODE_CMND)
	{
		if (node->args && node->args[0])
			printf("%s\n", node->args[0]);
	}


	// Print filename if redirect
	if (node->type == NODE_REDIRECT && node->file)
	{
		i = 0;

		while (i < (indent + 4))
		{
			printf(" ");
			i++;
		}
		printf("%s\n", node->file);
	}

	// Print all arguments for command, except the first
	if (node->type == NODE_CMND && node->args)
	{
		int	j;

		i = 1;
		while (node->args[i])
		{
			j = 0;
			while (j < (indent + 4))
			{
				printf(" ");
				j++;
			}
			printf("%s\n", node->args[i]);
			i++;
		}
	}

	print_ast(node->left, indent + 4);
}