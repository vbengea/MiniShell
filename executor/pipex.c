/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/19 17:28:58 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void	navigate_pipex(t_ast_node *node, t_terminal *tty)
{
	t_ast_node	*parent;

	parent = NULL;
	if (node)
	{
		node = node->right;
		while (node && node->left != NULL)
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
		}
		if (node)
			pipex(node, tty);
	}
}

static	void	parent(int fd[2], t_ast_node *node, int ppid, t_terminal *tty)
{
	t_ast_node	*origin;

	(void) ppid;
	origin = node;
	tty->files[0] = fd[0];
	node = node->parent;
	while (node)
	{
		if (node->type == NODE_PIPE && node->discovered == 0)
		{
			node->discovered = 1;
			break ;
		}
		node = node->parent;
	}
	navigate_pipex(node, tty);
	close(fd[0]);
	waiter(origin, tty);
}

static	void	child(int fd[2], t_ast_node *node, t_terminal *tty)
{
	pipex_redirect_in(node, fd, is_last(node, tty), tty);
	pipex_redirect_out(node, fd, is_last(node, tty), tty);
	if (node->type == NODE_CMND)
	{
		parse_command(node, tty);
		if (is_builtin(node))
		{
			builtin_selector(node, 1, tty);
		}
		else
		{
			if (execute(node, node->args, tty) == -1)
				cleanup("Error executing command", 126, node, tty);
		}
	}
	else
		navigator(node, 1, tty);
}

void	pipex(t_ast_node *node, t_terminal *tty)
{
	int			fd[2];
	int			pid;

	if (pipe(fd) == -1)
		cleanup("Error creating pipe", 1, node, tty);
	pid = fork();
	if (pid == -1)
		cleanup("Error forking process", 1, node, tty);
	if (pid == 0)
	{
		close(fd[0]);
		if (node)
			child(fd, node, tty);
		else
			close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (node)
			parent(fd, node, pid, tty);
		else
			close(fd[0]);
	}
}

int	in_redirect_first(t_ast_node *node, t_terminal *tty)
{
	if (node)
	{
		nullify_exit(node);
		detect_in_redirection(node, tty);
		traverse_pipex(node, tty, in_redirect_first);
	}
	return (1);
}
