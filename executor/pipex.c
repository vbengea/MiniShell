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

static	void	parent(int fd[2], t_ast_node *node, char ***env, int files[3], int ppid)
{
	int	pid;
	int	nid;

	(void) pid;
	(void) ppid;
	(void) nid;
	close(fd[1]);
	files[0] = fd[0];
	// pid = wait(NULL);
	if (!node)
		return ;
	waiter(node->type, node, env, files);
	if (node->side == 0)
	{
		if (node->parent->type == NODE_GROUP)
			node = node->parent;
		pipex(node->parent->right, env, files);
	}
	else if (!is_last(node, files))
	{
		node = node->parent->parent;
		if (node && node->type == NODE_GROUP)
			node = node->parent;
		pipex(node->right, env, files);
	}
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
		if (node)
			child(fd, node, env, files);
	}
	else
		parent(fd, node, env, files, pid);
}
