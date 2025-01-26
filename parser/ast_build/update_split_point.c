/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_split_point.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:33:11 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/26 11:43:02 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_token	*update_split_point(t_token *current, int *min_precedence, \
			t_token *split_point)
{
	if ((current->type == TOKEN_AND || current->type == TOKEN_OR)
		&& *min_precedence >= 1)
	{
		*min_precedence = 1;
		return (current);
	}
	if (current->type == TOKEN_PIPE && *min_precedence >= 2)
	{
		*min_precedence = 2;
		return (current);
	}
	if ((current->type == TOKEN_REDIRECT_IN
			|| current->type == TOKEN_REDIRECT_OUT
			|| current->type == TOKEN_APPEND) && *min_precedence >= 3)
	{
		*min_precedence = 3;
		return (current);
	}
	return (split_point);
}
