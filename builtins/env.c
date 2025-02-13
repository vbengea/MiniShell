/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/13 23:57:25 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*get_env(char *var, t_terminal *tty)
{
	int		i;

	i = env_lookup(var, tty);
	if (i >= 0)
		return (tty->env[i] + ft_strlen(var) + 1);
	return (NULL);
}

static	void	sort_env(t_ast_node *node, t_terminal *tty)
{
	int			i;
	char		*str;
	char		**p;

	p = copy_arr_of_strs(tty->env, 0, 0);
	if (p)
	{
		sort_arr_of_strs(p, 1);
		i = 0;
		while (p && p[i])
		{
			if (node->out_fd < 0)
				printf("declare -x %s\n", p[i++]);
			else
			{
				str = ft_strjoin("declare -x ", p[i++]);
				ft_putstrnl_fd(str, node->out_fd);
				free(str);
			}
		}
		clear_arr_of_strs(p);
	}
}

void	env_bi(t_ast_node *node, int sorted, t_terminal *tty)
{
	int			i;

	if (sorted)
		sort_env(node, tty);
	else
	{
		i = 0;
		while (tty->env && tty->env[i])
		{
			if (node->out_fd < 0)
				printf("%s\n", tty->env[i]);
			else
				ft_putstrnl_fd(tty->env[i], node->out_fd);
			i++;
		}
	}
}
