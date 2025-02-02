/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/25 16:37:00 by juaflore         ###   ########.fr       */
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


void		echo_bi(char **params, char **env)
{
	int		i;
	int		j;
	char	**s;
	char	*str;

	(void) env;
	i = 1;
	while (params[i])
	{
		clean_quotes(params[i]);
		s = ft_split(params[i], ' ');
		if (s)
		{
			j = 0;
			while (s[j])
			{
				if (s[j][0] == '$')
				{
					str = get_env((s[j] + 1), env);
					if (str)
						printf("%s", str);
					else
						printf("%s ", "");
				}
				else
					printf("%s", s[j]);
				j++;
			}
			printf(" ");
			clear_arr_of_strs(s);
		}
		i++;
	}
	printf("\n");
}
