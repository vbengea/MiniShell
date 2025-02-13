/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/13 18:12:56 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*get_env(char *var, t_terminal *tty)
{
	int		i;
	int		len;

	i = 0;
	var = ft_strjoin(var, "=");
	len = ft_strlen(var);
	while (var && tty->env[i])
	{
		if (ft_strncmp(tty->env[i], var, len) == 0)
		{
			free(var);
			return (tty->env[i] + len);
		}
		i++;
	}
	free(var);
	return (NULL);
}

char	**set_env(char *key, char *value, t_terminal *tty)
{
	int		i;
	int		found;
	int		len;
	char	*str;
	char	*var;

	i = 0;
	found = 0;
	var = key;
	var = ft_strjoin(var, "=");
	if (!value)
		value = ft_strdup("");
	while (var && tty->env[i])
	{
		if (var && ft_strncmp(tty->env[i], var, ft_strlen(var)) == 0)
		{
			str = ft_strjoin(var, value);
			if (str)
			{
				free(tty->env[i]);
				len = ft_strlen(str);
				tty->env[i] = malloc(len + 1);
				if (tty->env[i])
				{
					ft_strlcpy(tty->env[i], str, len + 1);
					tty->env[i][len] = '\0';
				}
				free(str);
			}
			found = 1;
			break ;
		}
		i++;
	}
	if (!found)
	{
		if (var)
		{
			str = ft_strjoin(var, value);
			if (str)
			{
				tty->env = add_arr_of_strs(tty->env, str);
				free(str);
			}
		}
	}
	free(var);
	return (tty->env);
}

void	check_shlvl(t_terminal *tty)
{
	int		l;
	char	*lvl;

	lvl = getenv("SHLVL");
	if (lvl)
	{
		l = ft_atoi(lvl) + 1;
		lvl = ft_itoa(l);
	}
	else
		lvl = ft_strdup("1");
	tty->env = set_env("SHLVL", lvl, tty);
	free(lvl);
}
