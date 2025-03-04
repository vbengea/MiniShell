/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:47:19 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:09:45 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	is_valid_operator(t_token_type type)
{
	return (type == TOKEN_PIPE
		|| type == TOKEN_AND
		|| type == TOKEN_OR);
}
