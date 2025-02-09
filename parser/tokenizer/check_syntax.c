/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:41:36 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/09 18:10:06 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

static bool is_valid_pipe(t_token *token, t_token *prev)
{
	if (!token)
		return (true);
	if (!prev && token->type == TOKEN_PIPE)
		return (false);
	if (token->type == TOKEN_PIPE && !token->next)
		return (false);
	if (token->type == TOKEN_PIPE && token->next && token->next->type == TOKEN_PIPE)
		return (false);
	return (true);
}

static bool	is_valid_redirection(t_token *token, t_token *prev)
{
	if (!token)
		return (true);
	if (is_redirect_token(token->type) && !token->next)
		return (false);
	if (is_redirect_token(token->type) && token->next && is_redirect_token(token->next->type))
		return (false);
	if (is_redirect_token(token->type) && prev && is_redirect_token(prev->type))
		return (false);
	return (true);
}
bool	check_syntax(t_token *tokens, t_token *prev)
{
	(void)prev;
	if (!tokens)
		return (true);
	if (tokens->type == TOKEN_INVALID)
		return (printf("Syntax error: INVALID TOKEN\n"), false);
	if (is_valid_pipe(tokens, prev))
		return (printf("Syntax error: INVALID PIPE\n"), false);
	if (is_valid_redirection(tokens, prev))
		return (printf("Syntax error: INVALID REDIRECTION\n"), false);
	return (check_syntax(tokens->next, prev));
}
