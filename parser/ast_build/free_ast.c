/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:47:26 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/15 11:22:32 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

static void	free_redirs(t_redirection *redir)
{
	t_redirection	*temp;

	while (redir)
	{
		temp = redir->next;
		if (redir->file)
		{
			free(redir->file);
			redir->file = NULL;
		}
		free(redir);
		redir = temp;
	}
	redir = NULL;
}

void	free_ast(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	free_redirs(node->redirs);
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			free(node->args[i]);
			node->args[i] = NULL;
			i++;
		}
		free(node->args);
		node->args = NULL;
	}
	node->left = NULL;
	node->right = NULL;
	node->redirs = NULL;
	free(node);
}
