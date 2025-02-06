/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_split_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea <vbengea@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:28:56 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/05 11:58:29 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

// t_token	*find_split_point(t_token *tokens)
// {
// 	t_token	*current;
// 	t_token	*split_point;
// 	int		miin_precedence;
// 	int		paren_level;

// 	current = tokens;
// 	split_point = NULL;
// 	miin_precedence = 100;
// 	paren_level = 0;
// 	while (current)
// 	{
// 		update_paren_level(&paren_level, current->type);
// 		if (paren_level == 0)
// 			update_split_point(&split_point, current, &miin_precedence);
// 		current = current->next;
// 	}
// 	return (split_point);
// }


// t_token *find_split_point(t_token *tokens)
// {
// 	t_token *current;
// 	t_token *split_point;
// 	int min_precedence;
// 	int paren_level;

// 	current = tokens;
// 	split_point = NULL;
// 	min_precedence = 100; // Start with a high precedence value
// 	paren_level = 0;

// 	while (current)
// 	{
// 		update_paren_level(&paren_level, current->type);

// 		// Only consider operators outside parentheses
// 		if (paren_level == 0)
// 		{
// 			if ((current->type == TOKEN_AND || current->type == TOKEN_OR) && min_precedence >= 1)
// 			{
// 				min_precedence = 1;
// 				split_point = current;
// 			}
// 			else if (current->type == TOKEN_PIPE && min_precedence >= 2)
// 			{
// 				min_precedence = 2;
// 				split_point = current;
// 			}
// 			else if (is_redirect_token(current->type) && min_precedence >= 3)
// 			{
// 				min_precedence = 3;
// 				split_point = current;
// 			}
// 		}

// 		// Debug print
// 		// printf("Current token: type=%d, value=%s\n", current->type, current->value);
// 		// printf("Split point: type=%d, value=%s\n", split_point ? split_point->type : (t_token_type)-1, split_point ? split_point->value : "NULL");

// 		current = current->next;
// 	}

// 	return (split_point);
// }


t_token *find_split_point(t_token *tokens)
{
	t_token *current;
	t_token *split_point;
	int min_precedence;
	int paren_level;

	current = tokens;
	split_point = NULL;
	min_precedence = 100; // Start with a high precedence value
	paren_level = 0;

	while (current)
	{
		update_paren_level(&paren_level, current->type);

		if (paren_level == 0)
		{
			if ((current->type == TOKEN_AND || current->type == TOKEN_OR) && min_precedence >= 1)
			{
				min_precedence = 1;
				split_point = current;
			}
			else if (current->type == TOKEN_PIPE && min_precedence >= 2)
			{
				min_precedence = 2;
				split_point = current;
			}
		}
		current = current->next;
	}

	return (split_point);
}