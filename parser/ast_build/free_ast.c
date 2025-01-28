/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:47:26 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/28 18:51:39 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

void	free_ast(t_ast_node *node)
{
	char	**cmd_args;
	int		i;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_CMND || node->type == NODE_REDIRECT)
	{
		cmd_args = (char **)node->args;
		if (cmd_args)
		{
			i = 0;
			while (cmd_args[i])
			{
				free(cmd_args[i]);
				i++;
			}
			free(cmd_args);
		}
	}
	free(node);
}
