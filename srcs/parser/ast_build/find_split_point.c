/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_split_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:28:56 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:11:04 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static void	determine_split_point(t_token *current, t_token **split_point, \
	int *min_precedence, int paren_level)
{
	if (paren_level == 0)
	{
		if ((current->type == TOKEN_AND || current->type == TOKEN_OR)
			&& *min_precedence >= 1)
		{
			*min_precedence = 1;
			*split_point = current;
		}
		else if (current->type == TOKEN_PIPE && *min_precedence >= 2)
		{
			*min_precedence = 2;
			*split_point = current;
		}
	}
}

t_token	*find_split_point(t_token *tokens)
{
	t_token	*current;
	t_token	*split_point;
	int		min_precedence;
	int		paren_level;

	current = tokens;
	split_point = NULL;
	min_precedence = 100;
	paren_level = 0;
	while (current)
	{
		update_paren_level(&paren_level, current->type);
		determine_split_point(current, &split_point, \
			&min_precedence, paren_level);
		current = current->next;
	}
	return (split_point);
}
