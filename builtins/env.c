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

void		env_bi(t_ast_node *node, char **env, int sorted)
{
	int			i;
	char		**p;
	char		*str;

	(void) p;
	p = NULL;
	i = 0;
	if (sorted)
	{
		p = copy_arr_of_strs(env, 0);
		if (p)
		{
			sort_arr_of_strs(p, 1);
			while (p && p[i])
				if (node->fd < 0)
					printf("declare -x %s\n", p[i++]);
				else
				{
					str = ft_strjoin("declare -x ", p[i++]);
					ft_putstrnl_fd(str, node->fd);
					free(str);
				}
			clear_arr_of_strs(p);
		}
	}
	else
		while (env && env[i])
		{
			if (node->fd < 0)
				printf("%s\n", env[i++]);
			else
				ft_putstrnl_fd(env[i++], node->fd);
		}
}
