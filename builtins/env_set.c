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

int	env_lookup(char *key, t_terminal *tty)
{
	int		i;
	char	*var;

	i = 0;
	var = key;
	var = ft_strjoin(var, "=");
	if (var)
	{
		while (tty->env[i])
		{
			if (ft_strncmp(tty->env[i], var, ft_strlen(var)) == 0)
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

void	append_entry(char *entry, t_terminal *tty)
{
	tty->env = add_arr_of_strs(tty->env, entry);
}

void	update_entry(char *entry, int i, t_terminal *tty)
{
	int	len;

	free(tty->env[i]);
	len = ft_strlen(entry);
	tty->env[i] = malloc(len + 1);
	if (tty->env[i])
	{
		ft_strlcpy(tty->env[i], entry, len + 1);
		tty->env[i][len] = '\0';
	}
	else
		cleanup("Error allocating memory");
}

void	set_env(t_ast_node *node, char *key, char *value, t_terminal *tty)
{
	char	*str;
	int		i;

	(void) node;
	str = get_entry(key, value);
	if (str)
	{
		i = env_lookup(key, tty);
		if (i < 0)
			append_entry(str, tty);
		else
			update_entry(str, i, tty);
		free(str);
	}
}
