/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:15:33 by jflores           #+#    #+#             */
/*   Updated: 2025/02/20 09:21:27 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	pipex_redirect_in(t_ast_node *node, int fd[2], int is_last, \
	t_terminal *tty)
{
	if (node->in_fd > 0)
	{
		(void) is_last;
		(void) fd;
	}
	else if (dup2(tty->files[0], STDIN_FILENO) == -1)
		perror("(1) Error redirecting");
}

void	pipex_redirect_out(t_ast_node *node, int fd[2], int is_last, \
	t_terminal *tty)
{
	(void) tty;
	if (detect_out_redirection(node, tty))
		close(fd[1]);
	else if (is_last)
		close(fd[1]);
	else if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("(3) Error redirecting");
}

t_ast_node	*compute_parent(t_ast_node *node)
{
	node = node->parent;
	while (node)
	{
		if (node->type == NODE_PIPE && node->traversed == 0)
		{
			node->traversed = 1;
			break ;
		}
		node = node->parent;
	}
	return (node);
}

void	traverse_pipex(t_ast_node *node, t_terminal *tty, \
	int (*f)(t_ast_node *, t_terminal *))
{
	t_ast_node	*parent;

	node = compute_parent(node);
	parent = NULL;
	if (node)
	{
		node = node->right;
		while (node && node->left != NULL)
		{
			parent = node;
			if (node->right)
			{
				node->right->parent = parent;
				node->right->side = 1;
			}
			node->left->parent = parent;
			node->left->side = 0;
			node = node->left;
		}
		if (node)
		{
			f(node, tty);
		}
	}
}

void	nullify_exit(t_ast_node *node)
{
	if (node->args[0] && ft_cmpexact(node->args[0], "exit"))
	{
		free(node->args[0]);
		node->args[0] = ft_strdup("echo");
		if (node->args[1])
		{
			free(node->args[0]);
			node->args[0] = ft_strdup("-n");
		}
	}
}
