/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/11 17:54:31 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	**export_bi(t_ast_node *node, char **env)
{
	char	*key;
	char	*value;

	key = node->args[1];
	value = node->args[2];
	if (env && (!key || !value))
	{
		env_bi(node, env, 1);
		return (env);
	}
	else if (env && key && value)
		env = set_env(key, value, env);
	return (env);
}
