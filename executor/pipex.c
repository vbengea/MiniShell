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

static	int	is_last_node(t_ast_node *node)
{
	if (node->type == NODE_CMND && node->side == 1)
	{
		if ((node->parent && node->parent->type == NODE_PIPE && \
			node->parent->parent && \
			node->parent->parent->type != NODE_PIPE) || !node->parent->parent)
			return (1);
	}
	return (0);
}

static	void	redirect(int fd[2], int files[2], int is_last)
{
	if (files[0] == -1)
	{
		perror("Error reading file");
		exit(1);
	}
	if (dup2(files[0], STDIN_FILENO) == -1)
		perror("Error redirecting");
	if (is_last)
	{
		if (dup2(files[1], STDOUT_FILENO) == -1)
			perror("Error redirecting");
	}
	else if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("Error redirectingT");
	close(fd[0]);
}

static	void	parent(int fd[2], int files[2], t_ast_node *node, char **env)
{
	if (!node)
		return ;
	close(fd[1]);
	if (node->side == 0)
	{
		files[0] = fd[0];
		pipex(node, env, files, 1);
	}
	else
		close(fd[0]);
	waiter(node->type);
}

static	void	child(int fd[2], int files[2], t_ast_node *node, char **env)
{
	if (!node)
	{
		exit(0);
		return ;
	}
	if (is_last_node(node))
		node->side = 1;
	redirect(fd, files, node->side);
	if (node->type == NODE_CMND)
	{
		if (execute(node->args, env) == -1)
			cleanup("Error executing command..");
	}
	else
	{
		close(files[0]);
		pipex(node, env, files, 0);
	}
}

void    pipex(t_ast_node *node, char **env, int files[], int side)
{
	int	fd[2];
	int	pid;

	if (!node)
		return ;
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
			parent(fd, files, node->right, env);
		else
			parent(fd, files, node, env);
	}
}
