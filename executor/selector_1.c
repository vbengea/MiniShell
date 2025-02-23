/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/23 12:33:39 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void	builtin(t_ast_node *node, int hold, t_terminal *tty)
{
	if (check_options(node, hold, tty))
	{
		preexecute(node, tty);
		builtin_selector(node, 0, tty);
		postexecute(node, tty);
		builtin_end(node, hold, tty);
	}
}

void	forker(t_ast_node *node, void (*f)(t_ast_node *node, int hold, \
	t_terminal *tty), t_terminal *tty)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		cleanup("Error forking process", 1, node, tty);
	if (pid == 0)
		f(node, 1, tty);
	else
		waiter(node, tty);
}

void	selector_node(t_ast_node *node, t_terminal *tty)
{
	t_ast_node *parent;

	parent = parent_no_group(node);
	if (parent)
	{
		if (parent->type == NODE_AND && tty->exit > 0)
			return ;
		if (parent->type == NODE_OR && tty->exit == 0)
			return ;
	}
	if (is_builtin(node))
	{
		if (is_pipe_state(node))
			forker(node, builtin, tty);
		else
			builtin(node, 0, tty);
	}
	else
		forker(node, executor, tty);
}

void	selector_pipe(t_ast_node *node, t_terminal *tty)
{
	t_ast_node	*parent;

	tty->files[2] = node->nid;
	while (node->left != NULL)
	{
		parent = node;
		if (node->right)
		{
			node->right->parent = parent;
			node->right->side = 1;
		}
		node->left->parent = parent;
		node->left->side = 0;
		node = node->left;
		if (node->type == NODE_GROUP && node->parent->type == NODE_GROUP)
			return ;
	}
	tty->files[0] = dup(STDIN_FILENO);
	in_redirect_first(node, tty);
	close(tty->files[0]);
	pipex(node, tty);
}

void	selector(t_ast_node *node, t_terminal *tty)
{
	if (node->type == NODE_CMND)
		selector_node(node, tty);
	else if (node->type == NODE_AND || node->type == NODE_OR)
		navigator(node, 1, tty);
	else if (node->type == NODE_PIPE)
		selector_pipe(node, tty);
	else if (node->type == NODE_GROUP && \
		(!node->parent || node->parent->type != NODE_GROUP))
	{
		preexecute(node, tty);
		forker(node, navigator, tty);
	}
}
