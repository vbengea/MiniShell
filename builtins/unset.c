/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/11 18:33:11 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*unset_str(char *key, int len)
{
	char	*str;

	str = malloc(len + 1 + 1);
	if (str)
	{
		ft_strcpy(str, key);
		str[len] = '=';
		str[len + 1] = '\0';
	}
	return (str);
}

char	**unset_bi(t_ast_node *node, char **env)
{
	int		i;
	int		len;
	char	*str;

	len = ft_strlen(node->args[1]);
	str = unset_str(node->args[1], len);
	i = 0;
	while (env && env[i])
	{
		if (ft_strnstr(env[i], str, len + 1))
		{
			free(env[i]);
			while (env && env[i])
			{
				env[i] = env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
	free(str);
	return (copy_arr_of_strs(env, 0, 1));
}
