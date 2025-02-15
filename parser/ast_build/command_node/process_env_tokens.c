/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:33:44 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/15 21:12:09 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"

void	process_env_tokens(char **env_tokens, char **cmd_args, \
	t_ast_node *node, int *i)
{
	int	j;

	j = 0;
	while (env_tokens[j])
	{
		node->expand_flag[*i] = 1;
		cmd_args[*i] = ft_strdup(env_tokens[j]);
		(*i)++;
		j++;
	}
}
