/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/14 00:48:58 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

int	env_lookup(t_ast_node *node, char *key, int arg_index, t_terminal *tty)
{
	int		i;
	char	*var;
	char	**env;

	if (arg_index < 0 || (arg_index >= 0 && node->expand_flag[arg_index]))
		env = tty->env;
	else
		env = tty->env_local;
	i = 0;
	var = key;
	var = ft_strjoin(var, "=");
	if (var)
	{
		while (env[i])
		{
			if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			{
				free(var);
				return (i);
			}
			i++;
		}
		free(var);
	}
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
		if (!value)
		{
			free(var);
			cleanup("Error processing env variable\n");
		}
		str = ft_strjoin(var, value);
		free(var);
	}
	return (str);
}

static	void	append_entry(t_ast_node *node, char *entry, int arg_index, t_terminal *tty)
{
	if (arg_index < 0 || (arg_index >= 0 && node->expand_flag[arg_index]))
		tty->env = add_arr_of_strs(tty->env, entry);
	else
		tty->env_local = add_arr_of_strs(tty->env_local, entry);
}

static	void	update_entry(t_ast_node *node, char *entry, int arg_index, int i, t_terminal *tty)
{
	int		len;
	char	**env;

	env = tty->env;
	(void) arg_index;
	(void) node;
	free(env[i]);
	len = ft_strlen(entry);
	env[i] = malloc(len + 1);
	if (env[i])
	{
		ft_strlcpy(env[i], entry, len + 1);
		env[i][len] = '\0';
	}
	else
		cleanup("Error allocating memory");
}

void	set_env(t_ast_node *node, char *key, char *value, t_terminal *tty)
{
	char	*str;
	int		i;
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
		i = env_lookup(node, key, arg_index, tty);
		if (i < 0)
			append_entry(node, str, arg_index, tty);
		else
			update_entry(node, str, arg_index, i, tty);
		free(str);
	}
}
