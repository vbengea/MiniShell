/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/25 16:31:33 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void	waitit(t_node_type type)
{
	int		status;

	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			if (access("__tmp__", F_OK) == 0)
				unlink("__tmp__");
			if (status != 0 && type == NODE_AND)
				exit(0);
			else if (status == 0 && type == NODE_OR)
				exit(0);
			break ;
		}
	}
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
	waitit(node->type);
	close(fd[1]);
	if (node->side == 0)
	{
		files[0] = fd[0];
		binary(node, env, files, 1);
	}
	else
		close(fd[0]);
}

static	void	child(int fd[2], int files[2], t_ast_node *node, char **env)
{
	if (!node)
		return ;
	if (node->parent_type == NODE_AND || node->parent_type == NODE_OR || node->parent_type == NODE_GROUP)
		node->side = 1;
	redirect(fd, files, node->side);
	if (node->type == NODE_CMND)
	{
		if (execute(node->args, env) == -1)
			cleanup("Error executing command..");
	}
	else
	{
		binary(node, env, files, 0);
	}
}

void	binary(t_ast_node *node, char **env, int files[2], int side)
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
		if (side == 2)
		{
			child(fd, files, node, env);
		}
		else if(side == 1)
			child(fd, files, node->right, env);
		else
			child(fd, files, node->left, env);
	}
	else
	{
		if (side == 2)
		{
			node->side = 0;
			parent(fd, files, node, env);
		}
		else if (side == 1)
			parent(fd, files, node->right, env);
		else
			parent(fd, files, node, env);
	}
}
