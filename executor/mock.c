/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:22:19 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/24 10:30:03 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

t_node	*get_tree(void)
{
	t_node	*s;
	t_node	*t;

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
				t = s->children[0]->children[0]->children[0];
				if (t)
				{
					ennode(t, PIPE, 3);
					t->children[0]->type = EXEC;
					t->children[0]->value = "echo 1";
					t->children[1]->type = EXEC;
					t->children[1]->value = "cat -e";
					t->children[2]->type = EXEC;
					t->children[2]->value = "echo 2";
				}
				s->children[0]->children[0]->children[1]->type = EXEC;
				s->children[0]->children[0]->children[1]->value = "cat -e";
			}
			s->children[0]->children[1]->type = EXEC;
			s->children[0]->children[1]->value = "echo 3";
		}
		s->children[1]->type = EXEC;
		s->children[1]->value = "cat -e";
		s->children[2]->type = EXEC;
		s->children[2]->value = "cat -e";
	}

	return (s);
}

t_node*	get_stree(void)
{
	t_node	*s;

	s = malloc(sizeof(t_node));
	if (s)
	{
		ennode(s, PIPE, 4);
		s->children[0]->type = EXEC;
		s->children[0]->value = "echo 1";
		s->children[1]->type = EXEC;
		s->children[1]->value = "cat -e";
		s->children[2]->type = EXEC;
		s->children[2]->value = "cat -e";
		s->children[3]->type = EXEC;
		s->children[3]->value = "cat -e";
	}

	return (s);
}

t_node*	get_stree2(void)
{
	t_node	*s;

	s = malloc(sizeof(t_node));
	if (s)
	{
		ennode(s, AND, 3);
		s->children[0]->type = EXEC;
		s->children[0]->value = "echo 4";
		ennode(s->children[1], PIPE, 3);
		s->children[1]->children[0]->type = EXEC;
		s->children[1]->children[0]->value = "ls -l";
		s->children[1]->children[1]->type = EXEC;
		s->children[1]->children[1]->value = "cat -e";
		s->children[1]->children[2]->type = EXEC;
		s->children[1]->children[2]->value = "cat -e";
		ennode(s->children[2], PIPE, 2);
		s->children[2]->children[0]->type = EXEC;
		s->children[2]->children[0]->value = "ls /";
		s->children[2]->children[1]->type = EXEC;
		s->children[2]->children[1]->value = "cat -e";
	}

	return (s);
}

t_node*	get_stree3(void)
{
	t_node	*s;

	s = malloc(sizeof(t_node));
	if (s)
	{
		ennode(s, AND, 4);
		s->children[0]->type = EXEC;
		s->children[0]->value = "sleep 3";
		s->children[1]->type = EXEC;
		s->children[1]->value = "ls -l";
		s->children[2]->type = EXEC;
		s->children[2]->value = "sleep 3";
		s->children[3]->type = EXEC;
		s->children[3]->value = "ls -l";
	}

	return (s);
}

t_node*	get_stree4(void)
{
	t_node	*s;

	s = malloc(sizeof(t_node));
	if (s)
	{
		ennode(s, PIPE, 2);
		s->children[0]->type = EXEC;
		s->children[0]->value = "grep Cl";
		s->children[0]->stdin = HEREDOC;
		s->children[0]->stdin_value = "EOF";
		s->children[0]->stdout = OUTFILE;
		s->children[0]->stdout_value = "t2";
		s->children[1]->type = EXEC;
		s->children[1]->value = "ls -l";
	}

	return (s);
}
// echo 4 && ls -l | cat -e | cat -e && ls / | cat -e
// sleep 3 && ls -l && sleep 3 && ls -l
// << EOF grep Cl > t1 | ls -l
// ((echo 1 | cat -e | echo 2) | cat -e && echo 3) | cat -e | cat -e

// 							||							
// 													|
// 				&&							<< EOF		>>
// 		|				./mini.sh		cat -e				t2	
// ls -l		>
// 	cat -e		t2

// (ls -l | cat -e > t2 && ./mini.sh ) || (cat -e << EOF | >>t2)
// 1	OR
// 2	
