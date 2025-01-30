/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea <vbengea@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:02:12 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/30 09:03:50 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

bool	is_redirect_token(t_token_tpype type)
{
	return (type == TOKEN_REDIRECT_IN
			|| type == TOKEN_REDIRECT_OUT
			|| type == TOKEN_APPEND
			|| type == TOKEN_HEREDOC);
}
