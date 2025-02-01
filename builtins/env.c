/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/25 16:37:00 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void		env_bi(char **env, int sorted)
{
	int		i;
	char	**p;

	i = 0;
	if (sorted)
	{
		p = copy_arr_of_strs(env, 0);
		if (p)
		{
			sort_arr_of_strs(p, 1);
			while (p && p[i])
				printf("%s\n", p[i++]);
			clear_arr_of_strs(p);
		}
	}
	else
		while (env && env[i])
			printf("%s\n", env[i++]);
}
