/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/20 18:51:28 by jflores          ###   ########.fr       */
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
	if (!node)
	{
		close(fd[0]);
		close(fd[1]);
		return ;
	}
	origin = node;
	if (node->last)
	{
		if (dup2(STDOUT_FILENO, STDIN_FILENO) == -1)
			perror("(1) Error redirecting");
	}
	else
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			perror("(1) Error redirecting");
	}
	close(fd[0]);
	close(fd[1]);
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
	waiter(origin, tty);
}

static	void	child(int fd[2], t_ast_node *node, t_terminal *tty)
{
	if (node)
	{
		if (!detect_out_redirection(node, tty) && !node->last)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				perror("(3) Error redirecting");
		}
		close(fd[1]);
		close(fd[0]);
		if (node->type == NODE_CMND)
		{
			parse_command(node, tty);
			if (is_builtin(node))
			{
				builtin_selector(node, 1, tty);
			}
			else if (execute(node, node->args, tty) == -1)
				cleanup("Error executing command", 127, node, tty);
		}
		else
			navigator(node, 1, tty);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
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
		child(fd, node, tty);
	else
		parent(fd, node, pid, tty);
}
