/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parentheses.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:21:42 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/28 19:36:23 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node	*handle_parentheses(t_token *tokens)
{
	t_token		*end;
	t_token		*next_after_paren;
	t_ast_node	*inner;
	t_ast_node	*group_node;

	end = find_matching_paren(tokens);
	if (!end || (end->next && !is_valid_operator(end->next->type)
			&& !is_redirect_token(end->next->type)))
		return (NULL);
	next_after_paren = end->next;
	end->next = NULL;
	inner = build_ast(tokens->next);
	end->next = next_after_paren;
	group_node = create_ast_node(NODE_GROUP, NULL);
	group_node->left = inner;
	if (next_after_paren)
		return (build_operator_node(group_node, next_after_paren));
	return (group_node);
}
