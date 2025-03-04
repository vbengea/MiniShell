/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:30:39 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:10:05 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

t_ast_node	*build_command_node(t_token *tokens)
{
	t_ast_node	*node;
	char		**cmd_args;
	int			count;

	node = create_ast_node(NODE_CMND, NULL);
	if (!node)
		return (NULL);
	count = count_command_words(tokens);
	if (count < 0)
		return (NULL);
	cmd_args = allocate_cmd_args(count);
	if (!cmd_args)
		return (NULL);
	if (!fill_cmd_args(tokens, cmd_args, node))
		return (NULL);
	node->args = cmd_args;
	return (node);
}
