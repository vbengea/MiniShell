/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:34:12 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:10:21 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

t_redirect_type	get_redirect_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIRECT_OUT)
		return (REDIRECT_OUT);
	else if (token_type == TOKEN_REDIRECT_IN)
		return (REDIRECT_IN);
	else if (token_type == TOKEN_APPEND)
		return (REDIRECT_APPEND);
	else if (token_type == TOKEN_HEREDOC)
		return (REDIRECT_HEREDOC);
	else
		return (REDIRECT_NONE);
}
