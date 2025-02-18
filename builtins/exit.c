/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/18 19:50:03 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	exit_bi(t_ast_node *node, t_terminal *tty)
{
	int	exit_code;

	exit_code = 0;
	if (node->args[1])
		exit_code = ft_atoi(node->args[1]);
	if (node->out_fd < 0)
		printf("exit\n");
	else
		write(node->out_fd, "exit\n", 5);
	while (node->parent)
		node = node->parent;
	free_redirect_ast(node, 1);
	destroy_terminal(tty);
	if (exit_code && (exit_code > 0 && exit_code <= 255))
		exit(exit_code);
	else
		exit(0);
}
