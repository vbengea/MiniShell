/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:00:44 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/26 12:06:40 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node	*build_ast(t_token *tokens)
{
	t_token		*prev;
	t_token		*end;
	t_token		*split_point;
	t_ast_node	*left;
	t_ast_node	*right;

	if (!tokens)
		return (NULL);
	if (tokens->type == TOKEN_OPEN_PAREN)
	{
		end = findt_matching_paren(tokens);
		if (end)
			return (handle_parentheses(tokens, end));
	}
	split_point = find_split_point(tokens);
	if (!split_point)
		return (build_command_node(tokens));
	left = NULL;
	right = NULL;
	if (split_point != tokens)
	{
		prev = tokens;
		while (prev->next != split_point)
			prev = prev->next;
		prev->next = NULL;
		left = build_ast(tokens);
		prev->next = split_point;
	}
	if (split_point->next)
		right = build_ast(split_point->next);
	return (build_operator_node(split_point, left, right));
}
