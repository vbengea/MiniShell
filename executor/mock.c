/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:22:19 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/22 12:36:14 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static	void	exit_mock(char *msg)
{
	perror(msg);
	exit(1);
}

static	void	ennode(t_node *s, enum node_type type, int n)
{
    int		i;

	i = 0;
	s->type = type;
	s->children = malloc(sizeof(t_node *) * (n + 1));
	if (s->children)
	{
		while (i < n)
		{
			s->children[i] = malloc(sizeof(t_node));
			if (!s->children[i])
				exit_mock("Error allocating memory");
			i++;
		}
		s->children[n] = NULL;
	}
	else
		exit_mock("Error allocating memory");
}

void	print_tree(t_node	*s)
{
	(void) s;
}

t_node*	get_tree()
{
	t_node	*s;

	s = malloc(sizeof(t_node));
	if (s)
	{
		ennode(s, PIPE, 3);
		if (s->children[0])
		{
			ennode(s->children[0], AND, 2);
			if (s->children[0]->children[0])
			{
				ennode(s->children[0]->children[0], PIPE, 2);
				if (s->children[0]->children[0]->children[0])
				{
					ennode(s->children[0]->children[0]->children[0], PIPE, 3);
					s->children[0]->children[0]->children[0]->children[0]->type = EXEC;
					s->children[0]->children[0]->children[0]->children[1]->type = EXEC;
					s->children[0]->children[0]->children[0]->children[2]->type = EXEC;
				}
				s->children[0]->children[0]->children[1]->type = EXEC;
			}
			s->children[0]->children[1]->type = EXEC;
		}
		s->children[1]->type = EXEC;
		s->children[2]->type = EXEC;
	}

	return (s);
}

// 							||							
// 													|
// 				&&							<< EOF		>>
// 		|				./mini.sh		cat -e				t2	
// ls -l		>
// 	cat -e		t2

	// (ls -l | cat -e > t2 && ./mini.sh ) || (cat -e << EOF | >>t2)
	// 1	OR
	// 2	
