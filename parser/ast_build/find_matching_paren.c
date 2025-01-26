/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_matching_paren.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:25:03 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/26 11:28:35 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_token	*findt_matching_paren(t_token *tokens)
{
	int		paren_count;
	t_token	*end;

	paren_count = 1;
	end = tokens->next;
	while (end && paren_count > 0)
	{
		if (end->type == TOKEN_OPEN_PAREN)
			paren_count++;
		else if (end->type == TOKEN_CLOSE_PAREN)
			paren_count--;
		if (paren_count > 0)
			end = end->next;
	}
	if (paren_count == 0)
		return (end);
	return (NULL);
}
