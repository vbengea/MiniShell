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
	pipex_redirect(node, fd, files, node->side);
	if (node->type == NODE_CMND)
	{
		if (execute(node->args, *env) == -1)
			cleanup("Error executing command");
	}
	else
	{
		close(files[0]);
		files[0] = fd[1];
		if (node->type == NODE_PIPE)
			pipex(node, env, files, 0);
		else
			navigator(node, env, 1, files);
		close(files[1]);
	}
}

void	pipex(t_ast_node *node, char ***env, int files[3], int side)
{
	int			fd[2];
	int			pid;
	t_ast_node	*ast;

	if (!node)
		return ;
	files[2] = side;
	if(side == 1)
		ast = node->right;
	else
		ast = node->left;
	ast->parent = node;
	if (pipe(fd) == -1)
		cleanup("Error creating pipe");
	pid = fork();
	if (pid == -1)
		cleanup("Error forking process");
	if (pid == 0)
		child(fd, files, ast, env);
	else
	{
		if (side == 1)
		{
			parent(fd, files, ast, env);
			if (ast)
				waiter(ast->type, ast, env, files);
		}
		else
		{
			parent(fd, files, node, env);
			if (ast)
				waiter(ast->type, ast, env, files);
		}
	}
}
