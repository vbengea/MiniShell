/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:00:44 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/15 21:16:30 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"

t_ast_node	*build_ast(t_token *tokens)
{
	t_token		*split_point;
	t_ast_node	*left;

	if (!tokens)
		return (NULL);
	if (tokens->type == TOKEN_OPEN_PAREN)
		return (handle_parentheses(tokens));
	split_point = find_split_point(tokens);
	if (!split_point)
		return (build_command_node(tokens));
	left = NULL;
	if (split_point != tokens)
	{
		disconnect_tokens(tokens, split_point);
		left = build_ast(tokens);
		reconnect_tokens(tokens, split_point);
	}
	return (build_operator_node(left, split_point));
}
