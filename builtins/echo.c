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
					str = getenv((s[j] + 1));
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
