/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/20 10:32:58 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*get_env(t_ast_node *node, int arg_index, char *key, t_terminal *tty)
{
	int		i;
	char	**p;
	char	*value;

	(void) arg_index;
	i = env_lookup(key, node, tty);
	if (i >= 0)
	{
		p = env_resolution(tty, 1);
		if (p)
		{
			value = ft_strdup(p[i] + ft_strlen(key) + 1);
			clear_arr_of_strs(p);
			return (value);
		}
	}
	return (NULL);
}

void	unset_one(char *key, t_ast_node *node, t_terminal *tty)
{
	int		i;
	char	**env;
	int		len;

	len = 0;
	(void) node;
	while (tty->env[len])
		len++;
	i = env_lookup(key, tty->ast, tty);
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
	int	j;

	j = 1;
	while (node->args[j])
		unset_one(node->args[j++], node, tty);
}
