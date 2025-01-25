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

t_ast_node	*get_data_structure_0(void)
{
	t_ast_node	*s;

	s = malloc(sizeof(t_ast_node));
	if (s)
	{
		binode(s, NODE_PIPE, 0, NULL);
		binode(s->left, NODE_CMND, 3, (char *[]){ "ls", "-l", "./executor" });
		binode(s->right, NODE_CMND, 2, (char *[]){ "grep", "mock.c" });
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
		binode(s->right, NODE_CMND, 2, (char *[]){ "cat", "-e" });
		binode(s->left->left, NODE_PIPE, 0, NULL);
		binode(s->left->right, NODE_CMND, 2, (char *[]){ "cat", "-e" });
		binode(s->left->left->left, NODE_CMND, 2, (char *[]){ "ls", "-l" });
		binode(s->left->left->right, NODE_CMND, 2, (char *[]){ "cat", "-e" });
	}
	return (s);
}

// ((echo 1 | cat -e | echo 2) | cat -e && echo 3) | cat -e | cat -ev
t_ast_node	*get_data_structure_2(void)
{
	t_ast_node	*s;

	s = malloc(sizeof(t_ast_node));
	if (s)
	{
		binode(s, NODE_PIPE, 0, NULL);

		binode(s->left, NODE_AND, 0, NULL);
		binode(s->right, NODE_PIPE, 0, NULL);

		binode(s->left->left, NODE_PIPE, 0, NULL);
		binode(s->left->right, NODE_CMND, 2, (char *[]){ "echo", "3" });
		binode(s->right->left, NODE_CMND, 2, (char *[]){ "cat", "-e" });
		binode(s->right->right, NODE_CMND, 2, (char *[]){ "cat", "-e" });

		binode(s->left->left->left, NODE_PIPE, 0, NULL);
		binode(s->left->left->right, NODE_CMND, 2, (char *[]){ "cat", "-e" });

		binode(s->left->left->left->left, NODE_PIPE, 0, NULL);		
		binode(s->left->left->left->right, NODE_PIPE, 0, NULL);

		binode(s->left->left->left->right->left, NODE_CMND, 2, (char *[]){ "cat", "-e" });	
		binode(s->left->left->left->right->right, NODE_CMND, 2, (char *[]){ "echo", "2" });

		binode(s->left->left->left->left->left, NODE_CMND, 2, (char *[]){ "echo", "1" });
	}
	return (s);
}

// ((echo 1 | cat -e | echo 2) | cat -e && echo 3) | cat -e | cat -ev
t_ast_node	*get_data_structure_3(void)
{
	t_ast_node	*s;

	s = malloc(sizeof(t_ast_node));
	if (s)
	{
		binode(s, NODE_PIPE, 0, NULL);

		binode(s->left, NODE_AND, 0, NULL);
		binode(s->right, NODE_PIPE, 0, NULL);

		binode(s->left->left, NODE_PIPE, 0, NULL);
		binode(s->left->right, NODE_CMND, 2, (char *[]){ "echo", "3" });
		binode(s->right->left, NODE_CMND, 2, (char *[]){ "cat", "-e" });
		binode(s->right->right, NODE_CMND, 2, (char *[]){ "cat", "-e" });

		binode(s->left->left->left, NODE_PIPE, 0, NULL);
		binode(s->left->left->right, NODE_CMND, 2, (char *[]){ "cat", "-e" });

		binode(s->left->left->left->left, NODE_PIPE, 0, NULL);		
		binode(s->left->left->left->right, NODE_CMND, 2, (char *[]){ "echo", "2" });

		binode(s->left->left->left->left->left, NODE_PIPE, 0, NULL);
		binode(s->left->left->left->left->right, NODE_CMND, 2, (char *[]){ "cat", "-e" });

		binode(s->left->left->left->left->left->left, NODE_CMND, 2, (char *[]){ "echo", "1" });
	}
	return (s);
}