/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/18 17:52:03 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void	print_fd(int sorted, char *p, char *value)
{
	if (sorted)
		printf("declare -x %s\n", p);
	else if (value != NULL)
		printf("%s\n", p);
}

static	void	print_nfd(t_ast_node *node, int sorted, char *p, char *value)
{
	char		*str;

	if (sorted)
	{
		str = ft_strjoin("declare -x ", p);
		ft_putstrnl_fd(str, node->out_fd);
		free(str);
	}
	else if (value != NULL)
		ft_putstrnl_fd(p, node->out_fd);
}

static	void	print_env(t_ast_node *node, int sorted, char **p)
{
	int			i;
	char		**key_value;

	i = 0;
	while (p && p[i])
	{
		key_value = ft_split(p[i], '=');
		if (key_value)
		{
			if (node->out_fd < 0)
				print_fd(sorted, p[i], key_value[1]);
			else
				print_nfd(node, sorted, p[i], key_value[1]);
			clear_arr_of_strs(key_value);
		}
		i++;
	}
}

void	env_bi(t_ast_node *node, int sorted, t_terminal *tty)
{
	char		**p;

	p = env_resolution(tty);
	if (p)
	{
		if (sorted)
		{
			sort_arr_of_strs(p, 1);
			print_env(node, 1, p);
		}
		else
			print_env(node, 0, p);
		clear_arr_of_strs(p);
	}
}
