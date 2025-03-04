/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_split_point.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:49:35 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:09:56 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	update_split_point(t_token **split, t_token *current, int *min_prec)
{
	if ((current->type == TOKEN_AND
			|| current->type == TOKEN_OR) && *min_prec >= 1)
	{
		*min_prec = 1;
		*split = current;
	}
	else if (current->type == TOKEN_PIPE && *min_prec >= 2)
	{
		*min_prec = 2;
		*split = current;
	}
	else if (is_redirect_token(current->type) && *min_prec >= 3)
	{
		*min_prec = 3;
		*split = current;
	}
}
