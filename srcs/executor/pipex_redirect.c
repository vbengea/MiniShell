/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:15:33 by jflores           #+#    #+#             */
/*   Updated: 2025/03/04 19:07:25 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

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
	t_ast_node	*original;

	original = node;
	node = compute_parent(node);
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
			f(node, tty);
	}
	else
		original->last = 1;
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

int	in_redirect_first(t_ast_node *node, t_terminal *tty)
{
	if (node)
	{
		nullify_exit(node);
		detect_in_redirection(node, 0, tty);
		traverse_pipex(node, tty, in_redirect_first);
	}
	return (1);
}

void	child_redirect(int fd[2], t_ast_node *node, t_terminal *tty)
{
	if (node)
	{
		if (!detect_out_redirection(node, tty) && !node->last)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				perror("(3) Error redirecting");
		}
		if (node->in_fd > 0)
		{
			if (dup2(node->in_fd, STDIN_FILENO) == -1)
				perror("(4) Error redirecting");
			close(node->in_fd);
		}
		close(fd[1]);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
}
