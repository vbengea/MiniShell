/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/24 21:14:59 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void	baitit(t_node_type type)
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

static	void	bparent(int fd[2], int files[2], t_ast_node *node, char **env, int side)
{
	if (!node)
		return ;
	baitit(node->type);
	close(fd[1]);
	if (side == 0)
	{
		files[0] = fd[0];
		pipeit(node, env, files, 1);
	}
	else
		close(fd[0]);
}

static	void	bedirect(int fd[2], int files[2], int is_last)
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

static	void	bchild(int fd[2], int files[2], t_ast_node *node, char **env, int side, t_node_type type)
{
	if (!node)
		return ;
	if (type == NODE_AND)
	{
		side = 1;
	}
	bedirect(fd, files, side);
	if (node->type == NODE_CMND)
	{
		if (bexecute(node->args, env) == -1)
			cleanup("Error executing command");
	}
	else
	{
		pipeit(node, env, files, 0);
	}
}

void	pipeit(t_ast_node *node, char **env, int files[2], int side)
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
	if (pid == 0)
	{
		if (side)
			bchild(fd, files, node->right, env, side, node->type);
		else
			bchild(fd, files, node->left, env, side, node->type);
	}
	else
	{
		if (side)
			bparent(fd, files, node->right, env, side);
		else
			bparent(fd, files, node, env, side);
	}
}

void	binary(t_ast_node *s, char **env, int fd[2])
{
	if (s->type == NODE_PIPE)
	{
		pipeit(s, env, fd, 0);
	}
}
