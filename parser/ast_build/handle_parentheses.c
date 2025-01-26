/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parentheses.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:21:42 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/26 11:24:28 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node	*handle_parentheses(t_token *tokens, t_token *end)
{
	t_token		*next_after_paren;
	t_ast_node	*inner;

	next_after_paren = end->next;
	end->next = NULL;
	inner = build_ast(tokens->next);
	end->next = next_after_paren;

	if (next_after_paren)
		return (build_ast_with_inner(inner, next_after_paren));
	return (inner);
}