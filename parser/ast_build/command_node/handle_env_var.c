/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:33:04 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/15 20:33:12 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"

void handle_env_var(t_token *current, char **cmd_args, t_ast_node *node, int *i)
{
	char **env_tokens;

	cmd_args[*i] = ft_strdup("export");
	(*i)++;
	env_tokens = ft_split(current->value, '=');
	process_env_tokens(env_tokens, cmd_args, node, i);
	free_tab(env_tokens);
}
