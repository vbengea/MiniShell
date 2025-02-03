/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/25 16:31:33 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void	parent(int fd[2], int files[3], t_ast_node *node, char ***env)
{
	if (!node)
		return ;
	close(fd[1]);
	if (node->side == 0)
	{
		files[0] = fd[0];
		pipex(node, env, files, 1);
	}
	close(fd[0]);
}

static	void	child(int fd[2], int files[3], t_ast_node *node, char ***env)
{
	if (!node)
	{
		exit(0);
		return ;
	}
	if (is_last_node(node))
		node->side = 1;
	redirect(node, fd, files, node->side);
	if (node->type == NODE_CMND)
	{
		if (execute(node->args, *env) == -1)
			cleanup("Error executing command..");
	}
	else
	{
		close(files[0]);
		files[0] = fd[1];
		pipex(node, env, files, 0);
		close(files[0]);
		close(files[1]);
	}
}

void	pipex(t_ast_node *node, char ***env, int files[3], int side)
{
	int	fd[2];
	int	pid;

	if (!node)
		return ;
	if (node->type == NODE_PIPE || node->type == NODE_CMND)
	{
		if (pipe(fd) == -1)
			cleanup("Error creating pipe");
		pid = fork();
		if (pid == -1)
			cleanup("Error forking process");
		populate_node(node, side);
		if (pid == 0)
		{
			if(side == 1)
				child(fd, files, node->right, env);
			else
				child(fd, files, node->left, env);
		}
		else
		{
			if (side == 1)
			{
				parent(fd, files, node->right, env);
				waiter(node->right->type, node->right);
			}
			else
			{
				parent(fd, files, node, env);
				waiter(node->left->type, node->left);
			}
		}
	}
	else
	{
		files[2] = side;
		selector(node, env, files);
	}
}
