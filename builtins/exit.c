/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/07 02:41:44 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	exit_bi(t_ast_node *node, char **env)
{
	if (node->fd < 0)
		printf("exit\n");
	else
		write(node->fd, "exit\n", 5);
	while (node->parent)
		node = node->parent;
	free_redirect_ast(node, 1);
	clear_arr_of_strs(env);
	rl_clear_history();
	exit(0);
}
