/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:14:12 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/24 20:44:26 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void	args(t_ast_node *node, int n, char **args)
{
	node->args = malloc(sizeof(char **) * n);
	node->args = args;
}

t_ast_node	*get_data_structure_0(void)
{
	t_ast_node	*s;

	s = malloc(sizeof(t_ast_node));
	if (s)
	{
		binode(s, NODE_PIPE, 0, NULL);
		binode(s->left, NODE_CMND, 4, { "ls", "-l", "./executor", NULL });
		// s->left->args = malloc(sizeof(char **) * 4);
		// s->left->args[0] = "ls";
		// s->left->args[1] = "-l";
		// s->left->args[2] = "./executor";
		// s->left->args[3] = NULL;
		binode(s->right, NODE_CMND, 3, { "grep", "mock.c", NULL });
	}
	return (s);
}


t_ast_node	*get_data_structure_1(void)
{
	t_ast_node	*s;

	s = malloc(sizeof(t_ast_node));
	if (s)
	{
		binode(s, NODE_PIPE, 0, NULL);
		binode(s->left, NODE_PIPE, 0, NULL);
		binode(s->right, NODE_CMND, 0, NULL);
		s->right->args = malloc(sizeof(char **) * 3);
		s->right->args[0] = "cat";
		s->right->args[1] = "-e";
		s->right->args[2] = NULL;
		binode(s->left->left, NODE_PIPE, 0, NULL);
		binode(s->left->right, NODE_CMND, 0, NULL);
		s->left->right->args = malloc(sizeof(char **) * 3);
		s->left->right->args[0] = "cat";
		s->left->right->args[1] = "-e";
		s->left->right->args[2] = NULL;
		binode(s->left->left->left, NODE_CMND, 0, NULL);
		s->left->left->left->args = malloc(sizeof(char **) * 3);
		s->left->left->left->args[0] = "ls";
		s->left->left->left->args[1] = "-l";
		s->left->left->left->args[2] = NULL;
		binode(s->left->left->right, NODE_CMND, 0, NULL);
		s->left->left->right->args = malloc(sizeof(char **) * 3);
		s->left->left->right->args[0] = "cat";
		s->left->left->right->args[1] = "-e";
		s->left->left->right->args[2] = NULL;
	}
	return (s);
}

// ((echo 1 | cat -e | echo 2) | cat -e && echo 3 && echo 4) | cat -e | cat -e
t_ast_node	*get_data_structure_1(void)
{
	t_ast_node	*s;

	s = malloc(sizeof(t_ast_node));
	if (s)
	{
		binode(s, NODE_PIPE);

		binode(s->left, NODE_AND);
		binode(s->right, NODE_PIPE);

		binode(s->left->left, NODE_PIPE);
		binode(s->left->right, NODE_CMND);
		binode(s->right->left, NODE_CMND);
		binode(s->right->right, NODE_CMND);

		binode(s->left->left->left, NODE_PIPE);
		binode(s->left->left->right, NODE_CMND);

		binode(s->left->left->left->left, NODE_PIPE);		
		binode(s->left->left->left->right, NODE_CMND);

		binode(s->left->left->left->left->left, NODE_CMND);
	}
	return (s);
}