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

static	void	redirect(t_ast_node *node, int fd[2], int files[3], int is_last)
{
	if (files[0] == -1)
	{
		perror("Error reading file");
		exit(1);
	}
	if (node->parent->type == NODE_REDIRECT && \
		(node->parent->redirect_type == REDIRECT_OUT || \
		node->parent->redirect_type == REDIRECT_APPEND))
	{
		redirecter(node->parent, NULL, 1, files);
	}
	else
	{
		if (is_last)
		{
			if (dup2(files[1], STDOUT_FILENO) == -1)
				perror("Error redirecting");
		}
		else if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("Error redirectingT");
	}
	if (node->parent->type == NODE_REDIRECT && \
		(node->parent->redirect_type == REDIRECT_IN || \
		node->parent->redirect_type == REDIRECT_HEREDOC))
	{
		redirecter(node->parent, NULL, 1, files);
	}
	else
	{
		if (dup2(files[0], STDIN_FILENO) == -1)
			perror("Error redirecting");
	}
	close(fd[0]);
	close(fd[1]);
}

static	void	parent(int fd[2], int files[3], t_ast_node *node, char **env)
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

static	void	child(int fd[2], int files[3], t_ast_node *node, char **env)
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
		if (execute(node->args, env) == -1)
			cleanup("Error executing command..");
	}
	else
	{
		close(files[0]);
		pipex(node, env, files, 0);
		close(files[1]);
	}
}

void    pipex(t_ast_node *node, char **env, int files[3], int side)
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
			{
				if (node->right && node->right->type == NODE_REDIRECT)
				{
					populate_node(node->right, side);
					child(fd, files, node->right->left, env);
				}
				else
					child(fd, files, node->right, env);
			}
			else
			{
				if (node->left && node->left->type == NODE_REDIRECT)
				{
					populate_node(node->left, side);
					child(fd, files, node->left->left, env);
				}
				else
					child(fd, files, node->left, env);
			}
		}
		else
		{
			if (side == 1)
				parent(fd, files, node->right, env);
			else
				parent(fd, files, node, env);
		}
	}
	else
	{
		files[2] = side;
		selector(node, env, files);
	}
}
