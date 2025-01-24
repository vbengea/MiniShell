/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:14:12 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/24 13:02:22 by juaflore         ###   ########.fr       */
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
		binode(s->left, NODE_PIPE);
		binode(s->left->left, NODE_PIPE);
		binode(s->left->right, NODE_CMND);
		s->right->args = (char *[]){"cat", "-e", NULL};
		binode(s->left->left->left, NODE_CMND);
		s->right->args = (char *[]){"ls", "-l", NULL};
		binode(s->left->left->right, NODE_CMND);
		s->right->args = (char *[]){"cat", "-e", NULL};
		binode(s->right, NODE_CMND);
		s->right->args = (char *[]){"cat", "-e", NULL};
	}
	return (s);
}
