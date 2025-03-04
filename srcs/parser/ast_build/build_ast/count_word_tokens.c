/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:49:04 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:09:39 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	count_word_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current && current->type == TOKEN_WORD)
	{
		count++;
		current = current->next;
	}
	return (count);
}
