/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:50:17 by jflores           #+#    #+#             */
/*   Updated: 2025/02/23 12:34:04 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

extern int	g_sig;

void	set_history_status(int status, t_terminal *tty)
{
	char	*value;

	value = ft_itoa(status);
	if (value && tty->env)
	{
		set_env(NULL, "?", value, tty);
		free(value);
	}
}

t_ast_node	*parent_no_group(t_ast_node *node)
{
	t_ast_node	*parent;

	parent = NULL;
	if (node)
	{
		parent = node->parent;
		while (parent)
		{
			if (parent->type == NODE_AND || parent->type == NODE_OR)
				break ;
			parent = parent->parent;
		}
	}
	return (parent);
}

void	waiter_util(t_ast_node *node, int status, t_terminal *tty)
{
	char		*file;

	if (status >= SIGHUP && status <= (SIGSYS + 33))
		status += 128;
	else if (status > 256)
		status = status >> 8;
	tty->exit = status;
	node->exit = status;
	set_history_status(status, tty);
	if (status == 0)
		multiple_output_redirections(node, tty);
	file = tmp_path(node->nid, REDIRECT_IN, node, tty);
	if (file)
	{
		if (access(file, F_OK) == 0)
			unlink(file);
		free(file);
	}
}

void	waiter(t_ast_node *node, t_terminal *tty)
{
	int		status;

	status = 0;
	g_sig = 1;
	while (1)
	{
		if (waitpid(-1, &status, 0) > 0)
		{
			if (status != SIGINT)
				g_sig = 0;
			waiter_util(node, status, tty);
			break ;
		}
	}
}
