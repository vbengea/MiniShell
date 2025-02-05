/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/25 16:37:00 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	exit_bi(t_ast_node *node)
{
	if (node->fd < 0)
		printf("exit\n");
	else
		write(node->fd, "exit\n", 5);
	exit(0);
}
