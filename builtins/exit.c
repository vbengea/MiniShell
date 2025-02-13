/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/13 18:04:23 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	exit_bi(t_ast_node *node, t_terminal *tty)
{
	if (node->out_fd < 0)
		printf("exit\n");
	else
		write(node->out_fd, "exit\n", 5);
	while (node->parent)
		node = node->parent;
	free_redirect_ast(node, 1);
	clear_arr_of_strs(tty->env);
	rl_clear_history();
	exit(0);
}
