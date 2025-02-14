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

static	void	print_env(t_ast_node *node, int sorted, char **p)
{
	int			i;
	char		*str;

	i = 0;
	while (p && p[i])
	{
		if (node->out_fd < 0)
		{
			if (sorted)
				printf("declare -x %s\n", p[i]);
			else
				printf("%s\n", p[i]);
		}
		else if (sorted)
		{
			str = ft_strjoin("declare -x ", p[i]);
			ft_putstrnl_fd(str, node->out_fd);
			free(str);
		}
		else
			ft_putstrnl_fd(p[i], node->out_fd);
		i++;
	}
}

static	void	sort_env(t_ast_node *node, t_terminal *tty)
{
	char		**p;

	p = copy_arr_of_strs(tty->env, 0, 0);
	if (p)
	{
		sort_arr_of_strs(p, 1);
		print_env(node, 1, p);
		clear_arr_of_strs(p);
	}
}

void	env_bi(t_ast_node *node, int sorted, t_terminal *tty)
{
	if (sorted)
		sort_env(node, tty);
	else
		print_env(node, 0, tty->env);
}
