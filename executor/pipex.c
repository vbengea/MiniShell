/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/08 11:11:46 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

extern int SIGNAL;

static	void	parent(int fd[2], t_ast_node *node, char ***env, int files[3], int ppid)
{
	t_ast_node	*origin;
	t_ast_node	*parent;

	origin = node;
	parent = NULL;
	SIGNAL = ppid;
	files[0] = fd[0];
	node = node->parent;
	while (node)
	{
		if(node->type == NODE_PIPE && node->discovered == 0)
		{
			node->discovered = 1;
			break ;
		}
		node = node->parent;
	}
	if(node)
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
			pipex(node, env, files);
	}
	close(fd[0]);
	waiter(origin->type, origin, env, files);
}

static	void	child(int fd[2], t_ast_node *node, char ***env, int files[3])
{
	pipex_redirect_in(node, fd, files, is_last(node, files));
	pipex_redirect_out(node, fd, files, is_last(node, files));
	if (node->type == NODE_CMND)
	{
		parse_command(node, env);
		if (execute(node->args, *env) == -1)
			cleanup("Error executing command");
	}
	else
		navigator(node, env, 1, files);
}

void	pipex(t_ast_node *node, char ***env, int files[3])
{
	int			fd[2];
	int			pid;

	if (pipe(fd) == -1)
		cleanup("Error creating pipe");
	pid = fork();
	if (pid == -1)
		cleanup("Error forking process");
	if (pid == 0)
	{
		close(fd[0]);
		if (node)
			child(fd, node, env, files);
		else
			close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (node)
			parent(fd, node, env, files, pid);
		else
			close(fd[0]);
	}
}
