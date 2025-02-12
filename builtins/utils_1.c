/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/12 20:56:46 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*get_env(char *var, char **env)
{
	int		i;
	int		len;

	i = 0;
	var = ft_strjoin(var, "=");
	len = ft_strlen(var);
	while (var && env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
		{
			free(var);
			return (env[i] + len);
		}
		i++;
	}
	free(var);
	return (NULL);
}

char	**set_env(char *key, char *value, char **env)
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
		value = "";
	while (var && env[i])
	{
		if (var && ft_strncmp(env[i], var, ft_strlen(var)) == 0)
		{
			str = ft_strjoin(var, value);
			if (str)
			{
				free(env[i]);
				len = ft_strlen(str);
				env[i] = malloc(len + 1);
				if (env[i])
				{
					ft_strlcpy(env[i], str, len + 1);
					env[i][len] = '\0';
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
				env = add_arr_of_strs(env, str);
				free(str);
			}
			free(var);
		}
	}
	return (env);
}

void	check_shlvl(char ***env)
{
	int		l;
	char	*lvl;

	lvl = getenv("SHLVL");
	l = ft_atoi(lvl) + 1;
	lvl = ft_itoa(l);
	*env = set_env("SHLVL", lvl, *env);
	free(lvl);
}
