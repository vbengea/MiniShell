/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/25 16:49:17 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	cleanup(char *err)
{
	perror(err);
	exit(1);
}

int	is_last_node(t_ast_node *node)
{
	if (node->type == NODE_CMND && node->side == 1)
	{
		if ((node->parent && node->parent->type == NODE_PIPE && \
			(!node->parent->parent || node->parent->parent->type != NODE_PIPE)) )
			return (1);
	}
	return (0);
}

int    is_builtin(t_ast_node *node)
{
	char	*b[8] = { "cd", "echo", "env", "exit", "export", "pwd", "unset", NULL };
	int		i = 0;
	while (b[i])
	{
		if (ft_strncmp(node->args[0], b[i], ft_strlen(b[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int    is_pipe_state(t_ast_node *node)
{
	if (node->parent_type == NODE_PIPE)
		return (1);
	return (0);
}

void	populate_node(t_ast_node *node, int side)
{
	if (!node->left)
	{
		node->left = malloc(sizeof(t_ast_node));
		node->left->left = NULL;
		node->left->right = NULL;
	}
	if (!node->right)
	{
		node->right = malloc(sizeof(t_ast_node));
		node->right->left = NULL;
		node->right->right = NULL;
	}
	node->left->parent = node;
	node->right->parent = node;
	node->right->parent_type = node->type;
	node->left->parent_type = node->type;
	node->right->side = 1;
	node->left->side = 0;
	node->side = side;
}
