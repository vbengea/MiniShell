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

t_ast_node	*get_data_structure_1(void)
{
	t_ast_node	*s;

	s = malloc(sizeof(t_ast_node));
	if (s)
	{
		binode(s, NODE_PIPE);

		binode(s->left, NODE_CMND);
		s->left->args = malloc(sizeof(char **) * 3);
		s->left->args[0] = "ls";
		s->left->args[1] = "-l";
		s->left->args[2] = NULL;

		binode(s->right, NODE_CMND);
		s->right->args = malloc(sizeof(char **) * 3);
		s->right->args[0] = "grep";
		s->right->args[1] = ".c";
		s->right->args[2] = NULL;

		// binode(s->left, NODE_PIPE);
		// binode(s->right, NODE_CMND);
		// s->right->args = malloc(sizeof(char **) * 3);
		// s->right->args[0] = "cat";
		// s->right->args[1] = "-e";
		// s->right->args[2] = NULL;

		// binode(s->left->left, NODE_PIPE);
		// binode(s->left->right, NODE_CMND);
		// s->left->right->args = malloc(sizeof(char **) * 3);
		// s->left->right->args[0] = "cat";
		// s->left->right->args[1] = "-e";
		// s->left->right->args[2] = NULL;

		// binode(s->left->left->left, NODE_CMND);
		// s->left->left->left->args = malloc(sizeof(char **) * 3);
		// s->left->left->left->args[0] = "cat";
		// s->left->left->left->args[1] = "-e";
		// s->left->left->left->args[2] = NULL;
		
		// binode(s->left->left->right, NODE_CMND);
		// s->left->left->right->args = malloc(sizeof(char **) * 3);
		// s->left->left->right->args[0] = "cat";
		// s->left->left->right->args[1] = "-e";
		// s->left->left->right->args[2] = NULL;
	}
	return (s);
}
