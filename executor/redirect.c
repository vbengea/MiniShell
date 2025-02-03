/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/25 16:31:33 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

int	is_last_node(t_ast_node *node)
{
	if (node->type == NODE_CMND && node->side == 1)
	{
		if ((node->parent && node->parent->type == NODE_PIPE && \
			(!node->parent->parent || node->parent->parent->type != NODE_PIPE)) )
			return (1);
	}
	return (0);
}

void	redirect(t_ast_node *node, int fd[2], int files[3], int is_last)
{
	(void) node;
	if (files[0] == -1)
	{
		perror("Error reading file");
		exit(1);
	}
	if (node->redirs)
	{
		int tmp = open("__tmp__", O_WRONLY | O_CREAT, 0666);
		if (dup2(tmp, STDOUT_FILENO) == -1)
			perror("Error redirecting");
	}
	else if (is_last)
	{
		if (dup2(files[1], STDOUT_FILENO) == -1)
			perror("Error redirecting");
	}
	else if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("Error redirectingT");
	if (dup2(files[0], STDIN_FILENO) == -1)
		perror("Error redirecting");
	close(fd[0]);
	close(fd[1]);
}
