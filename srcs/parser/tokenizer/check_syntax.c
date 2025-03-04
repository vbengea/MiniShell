/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:41:36 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:12:31 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static bool	even_parentheses(t_token *token)
{
	t_token	*current;
	int		balance;

	balance = 0;
	current = token;
	while (current)
	{
		if (current->type == TOKEN_OPEN_PAREN)
			balance++;
		else if (current->type == TOKEN_CLOSE_PAREN)
		{
			balance--;
			if (balance < 0)
				return (false);
		}
		current = current->next;
	}
	return (balance == 0);
}

static bool	is_valid_pipe(t_token *token, t_token *prev)
{
	if (!token)
		return (true);
	if (!prev && token->type == TOKEN_PIPE)
		return (false);
	if (token->type == TOKEN_PIPE && !token->next)
		return (false);
	if (token->type == TOKEN_PIPE && token->next
		&& token->next->type == TOKEN_PIPE)
		return (false);
	return (true);
}

static bool	has_empty_parentheses(t_token *token)
{
	while (token && token->next)
	{
		if (token->type == TOKEN_OPEN_PAREN
			&& token->next->type == TOKEN_CLOSE_PAREN)
			return (true);
		token = token->next;
	}
	return (false);
}

bool	check_syntax(t_token *tokens, t_token *prev)
{
	t_token	*current;

	if (!tokens)
		return (true);
	if (is_logic_operator(tokens->type))
		return (printf("Syntax error: AND / OR at first token\n"), false);
	current = tokens;
	while (current)
	{
		if (!current->next && is_logic_operator(current->type))
			return (printf("Syntax error: AND / OR at last token\n"), false);
		if (current->type == TOKEN_INVALID)
			return (printf("Syntax error: INVALID TOKEN\n"), false);
		if (!is_valid_pipe(current, prev))
			return (printf("Syntax error: INVALID PIPE\n"), false);
		if (!is_valid_redirection(current, prev))
			return (printf("Syntax error: INVALID REDIRECTION\n"), false);
		prev = current;
		current = current->next;
	}
	if (!even_parentheses(tokens))
		return (printf("Syntax error: UNCLOSED PARENTHSES\n"), false);
	if (has_empty_parentheses(tokens))
		return (printf("Syntax error: EMPTY PARENTHESIS\n"), false);
	return (true);
}
