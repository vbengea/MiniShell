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

void	redirecter(t_ast_node *node, char **env, int hold, int files[3])
{
	(void) hold;
	int	f = 0;
	if (node->redirect_type == REDIRECT_OUT)
	{
		f = open(node->file, O_RDONLY | O_CREAT | O_TRUNC, 0777);
		if (dup2(f, STDOUT_FILENO) == -1)
			perror("Error redirecting");
	}
	else if (node->redirect_type == REDIRECT_IN)
	{
		f = open(node->file, O_RDONLY);
		if (dup2(f, STDIN_FILENO) == -1)
			perror("Error redirecting");
	}
	else if (node->redirect_type == REDIRECT_APPEND)
	{
		f = open(node->file, O_RDONLY | O_CREAT | O_APPEND, 0666);
		if (dup2(f, STDOUT_FILENO) == -1)
			perror("Error redirecting");
	}
	else if (node->redirect_type == REDIRECT_HEREDOC)
	{
		f = here_doc(node->file, STDIN_FILENO);
		if (dup2(f, STDIN_FILENO) == -1)
			perror("Error redirecting");
	}
	if (!node->parent || node->parent->type != NODE_PIPE)
		navigator(node, env, 1, files);
}
