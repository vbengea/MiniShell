/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_split_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:28:56 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/28 19:36:49 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_token	*find_split_point(t_token *tokens)
{
	t_token	*current;
	t_token	*split_point;
	int		miin_precedence;
	int		paren_level;

	current = tokens;
	split_point = NULL;
	miin_precedence = 100;
	paren_level = 0;
	while (current)
	{
		update_paren_level(&paren_level, current->type);
		if (paren_level == 0)
			update_split_point(&split_point, current, &miin_precedence);
		current = current->next;
	}
	return (split_point);
}
