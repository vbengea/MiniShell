/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/14 00:35:55 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	unset_bi(t_ast_node *node, t_terminal *tty)
{
	int		i;
	int		j;

	j = 1;
	while (node->args[j])
	{
		i = env_lookup(node, node->args[j], j, tty);
		if (i >= 0)
		{
			free(tty->env[i]);
			while (tty->env[i])
			{
				tty->env[i] = tty->env[i + 1];
				i++;
			}
		}
		j++;
	}
}
