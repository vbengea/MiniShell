/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/18 21:47:33 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

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

int	env_lookup(char *key, t_terminal *tty)
{
	char	**p;
	int		i;
	char	*var;

	p = env_resolution(tty, 1);
	if (!p)
		cleanup("Memory error on environment variable lookup", 1);
	i = 0;
	var = ft_strjoin(key, "=");
	if (var)
	{
		while (p[i])
		{
			if (ft_strncmp(p[i], var, ft_strlen(var)) == 0)
			{
				clear_arr_of_strs(p);
				free(var);
				return (i);
			}
			i++;
		}
		free(var);
	}
	clear_arr_of_strs(p);
	return (-1);
}

char	*get_entry(char *key, char *value)
{
	char	*str;
	char	*var;

	str = NULL;
	var = key;
	var = ft_strjoin(var, "=");
	if (var)
	{
		if (!value)
			value = "";
		str = ft_strjoin(var, value);
		free(var);
	}
	return (str);
}

static	void	append_entry(t_ast_node *node, char *entry, int arg_index, \
t_terminal *tty)
{
	if (arg_index < 0 || (arg_index >= 0 && node->expand_flag[arg_index] == 1))
		tty->env = add_arr_of_strs(tty->env, entry);
	else if (arg_index >= 0 && node->expand_flag[arg_index] == 2)
		tty->env_cmd = add_arr_of_strs(tty->env_cmd, entry);
	else
		tty->env_local = add_arr_of_strs(tty->env_local, entry);
}

void	set_env(t_ast_node *node, char *key, char *value, t_terminal *tty)
{
	char	*str;
	int		j;
	int		arg_index;

	arg_index = -1;
	if (node != NULL)
	{
		j = 0;
		while (node->args[j])
		{
			if (ft_cmpexact(node->args[j], key))
			{
				arg_index = j - 1;
				break ;
			}
			j++;
		}
	}
	str = get_entry(key, value);
	if (str)
	{
		unset_one(key, tty);
		append_entry(node, str, arg_index, tty);
		free(str);
	}
}
