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

static void	bedirect(int fd[2])
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		cleanup("Error redirecting");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		cleanup("Error redirecting");
}

static	void	baitit(t_node_type type)
{
	int		status;

	(void) type;
	while (1)
	{
		printf("NOPE\n");
		if (waitpid(-1, &status, 0) == -1)
		{
			printf("ACABO\n");
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

static void	bparent(int fd[2], t_ast_node *node, char **env, int side)
{
	if (!node)
		return ;
	baitit(node->type);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		cleanup("Error changing STD IN");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		cleanup("Error changing STD IN");
	if (!side)
	{
		close(fd[1]);
		pipeit(node, env, fd, 1);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}

}

static void	bchild(int fd[2], t_ast_node *node, char **env, int side)
{
	if (!node)
		return ;
	bedirect(fd);
	if (node->type == NODE_CMND)
	{
		if (bexecute(node->args, env) == -1)
			cleanup("Error executing command");
	}
	else
		pipeit(node, env, fd, side);

	close(fd[0]);
}

void	pipeit(t_ast_node *node, char **env, int files[2], int side)
{
	int	fd[2];
	int	pid;

	if (!node)
		return ;
	(void) files;
	if (pipe(fd) == -1)
		cleanup("Error creating pipe");

	pid = fork();
	if (pid == -1)
		cleanup("Error forking process");
	if (pid == 0)
	{
		// if (files)
		// {
		// 	fd[0] = files[0];
		// 	fd[1] = STDOUT_FILENO;
		// }
		fd[1] = files[0];
		if (side)
			bchild(files, node->right, env, side);
		else
			bchild(files, node->left, env, side);
	}
	else
	{
		if (side)
			bparent(fd, node->right, env, side);
		else
			bparent(fd, node, env, side);
	}
}

void	binary(t_ast_node *s, char **env, int fd[2])
{
	if (s->type == NODE_PIPE)
	{
		pipeit(s, env, fd, 0);
	}

}
