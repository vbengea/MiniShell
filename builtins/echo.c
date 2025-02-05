/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/04 10:49:57 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void		clean_quotes(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			j = 0;
			while (str[i + j])
			{
				str[i + j] = str[i + j + 1];
				j++;
			}
		}
		i++;
	}
}

char	*get_env(char *var, char **env)
{
	int	i;
	int len;

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

char	*set_env(char *var, char *value, char **env)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	while (env[i])
	{
		var = ft_strjoin(var, "=");
		if (var)
		{
			if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			{
				free(env[i]);
				str = ft_strjoin(var, value);
				len = ft_strlen(str);
				env[i] = malloc(len + 1);
				ft_strlcpy(env[i], str, len + 1);
				env[i][len] = '\0';
				free(str);
			}
			free(var);
		}
		i++;
	}
	return (NULL);
}

static	char *add_str(char *a, char *b)
{
	char	*t;

	t = a;
	a = ft_strjoin(a, b);
	free(t);
	return (a);
}

char	*interpolation(char *str, char **env)
{
	int		j;
	char	**s;
	char	*r;

	clean_quotes(str);
	s = ft_split(str, ' ');
	r = ft_strdup("");
	if (s)
	{
		j = 0;
		while (s[j])
		{
			if (s[j][0] == '$')
			{
				str = get_env((s[j] + 1), env);
				if (str)
					r = add_str(r, str);
				else
					r = add_str(r, " ");
			}
			else
				r = add_str(r, s[j]);
			j++;
		}
		clear_arr_of_strs(s);
	}
	return (r);
}


void		echo_bi(char **params, char **env)
{
	int		i;
	char	*str;

	i = 1;
	while (params[i])
	{
		str = interpolation(params[i], env);
		printf("%s ", str);
		free(str);
		i++;
	}
	printf("\n");
}
