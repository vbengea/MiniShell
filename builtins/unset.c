/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/06 00:11:03 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	**unset_bi(t_ast_node *node, char **env)
{
	int		i;
	int		len;
	char	*str;
	char	*key;

	key = node->args[1];
	i = 0;
	len = ft_strlen(key);
	str = malloc(len + 1 + 1);
	ft_strcpy(str, key);
	str[len] = '=';
	str[len + 1] = '\0';
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