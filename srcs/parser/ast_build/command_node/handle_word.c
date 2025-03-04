/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:32:19 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:10:42 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	handle_word(t_token *current, char **cmd_args, t_ast_node *node, int *i)
{
	cmd_args[*i] = ft_strdup(current->value);
	if (current->type == TOKEN_ENV_VAR || current->has_env)
		node->expand_flag[*i] = 1;
	if (current->has_space)
		node->has_space[*i] = 1;
	(*i)++;
}
