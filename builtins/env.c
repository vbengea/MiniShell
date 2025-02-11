/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/11 14:56:43 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void	sort_env(t_ast_node *node, char **env)
{
	int			i;
	char		*str;
	char		**p;

	p = copy_arr_of_strs(env, 0, 0);
	if (p)
	{
		sort_arr_of_strs(p, 1);
		i = 0;
		while (p && p[i])
		{
			if (node->out_fd < 0)
				printf("declare -x %s\n", p[i++]);
			else
			{
				str = ft_strjoin("declare -x ", p[i++]);
				ft_putstrnl_fd(str, node->out_fd);
				free(str);
			}
		}
		clear_arr_of_strs(p);
	}
}

void	env_bi(t_ast_node *node, char **env, int sorted)
{
	int			i;

	if (sorted)
		sort_env(node, env);
	else
	{
		i = 0;
		while (env && env[i])
		{
			if (node->out_fd < 0)
				printf("%s\n", env[i]);
			else
				ft_putstrnl_fd(env[i], node->out_fd);
			i++;
		}
	}
}
