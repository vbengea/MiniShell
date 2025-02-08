/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parentheses.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:21:42 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/08 11:46:13 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node *handle_parentheses(t_token *tokens)
{
	t_token *end;
	t_token *next_after_paren;
	t_ast_node *inner;
	t_ast_node *group_node;

	// Find the matching closing parenthesis
	end = find_matching_paren(tokens);
	if (!end)
		return NULL;

	// Temporarily disconnect the grouped command for parsing
	next_after_paren = end->next;
	end->next = NULL;

	// Build the inner command (inside the parentheses)
	inner = build_ast(tokens->next);

	// Reconnect the tokens
	end->next = next_after_paren;

	// Create the NODE_GROUP node
	group_node = create_ast_node(NODE_GROUP, NULL);
	group_node->left = inner;

	// Handle redirections after the closing parenthesis
	if (next_after_paren && is_redirect_token(next_after_paren->type))
	{
		t_redirect_type redirect_type;
		t_out_redirect_type otype = STDOUT_FILE; // Default

		// Determine the redirection type
		if (next_after_paren->type == TOKEN_REDIRECT_IN)
			redirect_type = REDIRECT_IN;
		else if (next_after_paren->type == TOKEN_REDIRECT_OUT)
			redirect_type = REDIRECT_OUT;
		else if (next_after_paren->type == TOKEN_APPEND)
			redirect_type = REDIRECT_APPEND;
		else
			redirect_type = REDIRECT_HEREDOC;

		// Move past the redirection operator and get the file token
		next_after_paren = next_after_paren->next;
		if (!next_after_paren || next_after_paren->type != TOKEN_WORD)
		{
			printf("Syntax error: Missing file after redirection\n");
			return NULL; // Syntax error
		}

		// Add the redirection to the NODE_GROUP's redirs list
		add_redirection(group_node, redirect_type, otype, ft_strdup(next_after_paren->value));

		// Move past the file token
		next_after_paren = next_after_paren->next;
	}

	// Handle operators after the redirection (if any)
	if (next_after_paren && is_valid_operator(next_after_paren->type))
		return build_operator_node(group_node, next_after_paren);

	return group_node;
}


// (((ls > t3) && ls) > t2 && ls) > t1