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

void	unset_one(t_ast_node *node, char *key, int j, t_terminal *tty)
{
	int		i;
	char	**env;
	int		len;

	len = 0;
	while (tty->env[len])
		len++;
	i = env_lookup(node, key, j, tty);
	if (i >= 0)
	{
		if (i < len)
			env = tty->env;
		else
		{
			i = i - len;
			env = tty->env_local;
		}
		free(env[i]);
		while (env[i])
		{
			env[i] = env[i + 1];
			i++;
		}
	}
}

void	unset_bi(t_ast_node *node, t_terminal *tty)
{
	int		j;

	j = 1;
	while (node->args[j])
	{
		unset_one(node, node->args[j], j, tty);
		j++;
	}
}
