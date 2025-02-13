/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/13 11:33:55 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	**export_bi(t_ast_node *node, char **env)
{
	char	*key;
	char	*value;
	int		len;
	int		i;
	int		j;

	len = 0;
	j = 0;
	while (node->args[len])
		len++;

	if (len == 1)
		env_bi(node, env, 1);
	else if (env)
	{
		i = 0;
		while (i < len && node->args[i])
		{
			key = node->args[i];
			if (ft_strncmp(key, "export", 6) == 0 && ft_strlen(key) == 6)
			{
				key = node->args[i + 1];
				value = node->args[i + 2];
				if (key && value)
					env = set_env(key, value, env);
				i += 2;
			}
			i++;
		}
	}
	return (env);
}
