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

char	*get_env(t_ast_node *node, int arg_index, char *key, t_terminal *tty)
{
	int		i;
	char	**p;
	char	*value;

	i = env_lookup(node, key, arg_index, tty);
	if (i >= 0)
	{
		p = env_resolution(tty);
		if (p)
		{
			value = ft_strdup(p[i] + ft_strlen(key) + 1);
			free(p);
			return (value);
		}
	}
	return (NULL);
}

static	void	print_env(t_ast_node *node, int sorted, char **p)
{
	int			i;
	char		*str;
	char		**key_value;

	i = 0;
	while (p && p[i])
	{
		key_value = ft_split(p[i], '=');
		if (key_value)
		{
			if (node->out_fd < 0)
			{
				if (sorted)
					printf("declare -x %s\n", p[i]);
				else if (key_value[1] != NULL)
					printf("%s\n", p[i]);
			}
			else
			{
				if (sorted)
				{
					str = ft_strjoin("declare -x ", p[i]);
					ft_putstrnl_fd(str, node->out_fd);
					free(str);
				}
				else if (key_value[1] != NULL)
					ft_putstrnl_fd(p[i], node->out_fd);
			}
			clear_arr_of_strs(key_value);
		}
		i++;
	}
}

static	void	sort_env(t_ast_node *node, t_terminal *tty)
{
	char		**p;
	int			i;

	i = 0;
	p = copy_arr_of_strs(tty->env, 0, 0);
	if (p)
	{
		while (p && tty->env_local[i])
			p = add_arr_of_strs(p, tty->env_local[i++]);
		if (p)
		{
			sort_arr_of_strs(p, 1);
			print_env(node, 1, p);
			clear_arr_of_strs(p);
		}
	}
}

void	env_bi(t_ast_node *node, int sorted, t_terminal *tty)
{
	if (sorted)
		sort_env(node, tty);
	else
		print_env(node, 0, tty->env);
}
