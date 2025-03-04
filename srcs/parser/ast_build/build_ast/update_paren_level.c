/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_paren_level.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:50:00 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:09:51 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	update_paren_level(int *level, t_token_type type)
{
	if (type == TOKEN_OPEN_PAREN)
		(*level)++;
	else if (type == TOKEN_CLOSE_PAREN)
		(*level)--;
}
