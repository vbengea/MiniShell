/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/25 16:37:00 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	pwd_bi(char **env)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	str = "PWD=";
	len = 4;
	while (env && env[i])
	{
		if (ft_strnstr(env[i], str, len))
		{
			printf("%s\n", (env[i] + len));
			break ;
		}
		i++;
	}
}
