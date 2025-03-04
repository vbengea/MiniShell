/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:00:44 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:09:34 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

t_ast_node	*build_ast(t_token *tokens)
{
	t_token		*split_point;
	t_token		*temp;
	t_ast_node	*left;

	temp = tokens;
	if (!temp)
		return (NULL);
	if (temp->type == TOKEN_OPEN_PAREN)
		return (handle_parentheses(temp));
	split_point = find_split_point(temp);
	if (!split_point)
		return (build_command_node(temp));
	left = NULL;
	if (split_point != temp)
	{
		disconnect_tokens(temp, split_point);
		left = build_ast(temp);
		reconnect_tokens(temp, split_point);
	}
	return (build_operator_node(left, split_point));
}
