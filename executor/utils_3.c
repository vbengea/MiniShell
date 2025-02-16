/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:44:28 by jflores           #+#    #+#             */
/*   Updated: 2025/02/16 19:46:33 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	ast_printer_node(t_ast_node *ast, int level, int i)
{
	printf("[TYPE:%d] [NID:%d] [SIDE:%d] [ARGS]: ", ast->type, \
		ast->nid, ast->side);
	i = 0;
	while (ast->args && ast->args[i])
	{
		printf("_%s_(%d, %d),", ast->args[i], ast->expand_flag[i], \
			ast->has_space[i]);
		i++;
	}
	printf("[REDIRS]: ");
	if (ast->redirs)
		redlist_iter(ast->redirs, print_redirs);
	printf("\n");
}

void	ast_printer(t_ast_node *ast, int level)
{
	int	i;

	if (ast)
	{
		i = 0;
		while (i++ < level)
			printf("  ");
		if (ast->type == NODE_CMND || ast->type == NODE_GROUP)
			print_ast_node(ast, level, i);
		else
			printf("[TYPE: %d] [NID:%d] [SIDE:%d] \n", ast->type, ast->nid, \
				ast->side);
		if (ast->left)
			ast_printer(ast->left, level + 1);
		if (ast->right)
			ast_printer(ast->right, level + 1);
	}
}