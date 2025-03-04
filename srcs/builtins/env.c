/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/03/04 19:06:35 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

char	**env_resolution(t_terminal *tty, int hidden_level)
{
	char		**p;
	int			i;

	p = copy_arr_of_strs(tty->env, 0, 0);
	if (p)
	{
		if (hidden_level)
		{
			i = 0;
			while (p && tty->env_local[i])
				p = add_arr_of_strs(p, tty->env_local[i++]);
		}
		i = 0;
		while (p && tty->env_cmd[i])
			p = add_arr_of_strs(p, tty->env_cmd[i++]);
	}
	return (p);
}

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

	p = env_resolution(tty, 0);
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
