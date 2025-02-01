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
		s = ft_split(params[i], ' ');
		j = 0;
		while (s[j])
		{
			if (s[j][0] == '$')
			{
				str = getenv((s[j] + 1));
				if (str)
					printf("%s ", str);
				else
					printf("%s ", "");
			}
			else
				printf("%s ", s[j]);
			j++;
		}
		i++;
	}
	printf("\n");
}
