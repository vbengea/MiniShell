/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:34:12 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/15 20:34:27 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"

t_redirect_type get_redirect_type(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN)
		return (REDIRECT_IN);
	if (type == TOKEN_REDIRECT_OUT)
		return (REDIRECT_OUT);
	if (type == TOKEN_APPEND)
		return (REDIRECT_APPEND);
	return (REDIRECT_HEREDOC);
}
