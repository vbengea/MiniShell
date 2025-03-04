/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:00:40 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:12:27 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static bool	token_is_dash(t_token *token)
{
	return (token && token->type == TOKEN_WORD
		&& token->value && ft_cmpexact(token->value, "-"));
}

bool	is_logic_operator(t_token_type type)
{
	return (type == TOKEN_AND || type == TOKEN_OR);
}

static bool	is_invalid_redirection_with_operator(t_token *token, t_token *other)
{
	return (token && is_redirect_token(token->type)
		&& other && is_logic_operator(other->type));
}

bool	is_valid_redirection(t_token *token, t_token *prev)
{
	if (!token)
		return (true);
	if (is_redirect_token(token->type) && !token->next)
		return (false);
	if (is_redirect_token(token->type) && token->next
		&& is_redirect_token(token->next->type))
		return (false);
	if (is_redirect_token(token->type) && prev
		&& is_redirect_token(prev->type))
		return (false);
	if (is_redirect_token(token->type)
		&& (token_is_dash(prev) || token_is_dash(token->next)))
		return (false);
	if (is_invalid_redirection_with_operator(token, prev)
		|| is_invalid_redirection_with_operator(token, token->next))
		return (false);
	return (true);
}
