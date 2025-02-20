/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:50:17 by jflores           #+#    #+#             */
/*   Updated: 2025/02/20 09:49:03 by jflores          ###   ########.fr       */
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

void	waiter_util(t_ast_node *node, int status, t_terminal *tty)
{
	char		*file;
	t_ast_node	*parent;

	if (status >= SIGHUP && status <= (SIGSYS + 33))
		status += 128;
	else if (status > 256)
		status = status >> 8;
	parent = node->parent;
	while (parent)
	{
		parent->exit = status;
		parent = parent->parent;
	}
	node->exit = status;
	set_history_status(status, tty);
	if (status == 0)
		multiple_output_redirections(node, tty);
	file = tmp_path(node->nid, REDIRECT_IN);
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
