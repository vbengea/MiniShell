/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parentheses.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:21:42 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/15 20:13:59 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

static void	handle_redirection_after_paren(t_ast_node *group_node, \
	t_token **next_after_paren)
{
	t_redirection_info	redir_info;

	if (*next_after_paren && is_redirect_token((*next_after_paren)->type))
	{
		redir_info.otype = STDOUT_FILE;
		if ((*next_after_paren)->type == TOKEN_REDIRECT_IN)
			redir_info.type = REDIRECT_IN;
		else if ((*next_after_paren)->type == TOKEN_REDIRECT_OUT)
			redir_info.type = REDIRECT_OUT;
		else if ((*next_after_paren)->type == TOKEN_APPEND)
			redir_info.type = REDIRECT_APPEND;
		else
			redir_info.type = REDIRECT_HEREDOC;
		*next_after_paren = (*next_after_paren)->next;
		if (!*next_after_paren || (*next_after_paren)->type != TOKEN_WORD)
			return ;
		redir_info.file = ft_strdup((*next_after_paren)->value);
		redir_info.quote_flag = 0;
		add_redirection(group_node, &redir_info);
		*next_after_paren = (*next_after_paren)->next;
	}
}

t_ast_node	*handle_parentheses(t_token *tokens)
{
	t_paren_context	context;
	t_ast_node		*group_node;

	context.end = find_matching_paren(tokens);
	if (!context.end)
		return (NULL);
	context.next_after_paren = context.end->next;
	context.end->next = NULL;
	context.inner = build_ast(tokens->next);
	context.end->next = context.next_after_paren;
	group_node = create_ast_node(NODE_GROUP, NULL);
	group_node->left = context.inner;
	handle_redirection_after_paren(group_node, &context.next_after_paren);
	if (context.next_after_paren
		&& is_valid_operator(context.next_after_paren->type))
		return (build_operator_node(group_node, context.next_after_paren));
	return (group_node);
}
