/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/20 23:37:45 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

int	env_lookup(char *key, t_ast_node *node, t_terminal *tty)
{
	char	**p;
	int		i;
	char	*var;

	p = env_resolution(tty, 1);
	if (!p)
		cleanup("Memory error on environment variable lookup", 1, node, tty);
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

static	int	is_env_valid(char *key)
{
	int	i;
	int	start;
	int	between;

	start = 0;
	between = 1;
	if (key)
	{
		if (ft_isalpha(key[0]) || key[0] == '_' || (key[0] == '?' && ft_strlen(key) == 1))
			start = 1;
		if (ft_strlen(key) == 1)
			between = 1;
		else
		{
			i = 1;
			while (key[i])
			{
				if(key[i] != '_' && !ft_isalnum(key[i]))
				{
					between = 0;
					break ;
				}
				i++;
			}
		}
	}
	return (start && between);
}

void	set_env(t_ast_node *node, char *key, char *value, t_terminal *tty)
{
	char	*str;

	str = get_entry(key, value);
	if (str)
	{
		if (is_env_valid(key))
		{
			unset_one(key, node, tty);
			append_entry(node, str, get_arg_index(node, key), tty);
		}
		else
			printf("minishell: export: `%s': not a valid identifier\n", str);
		free(str);
	}
}
