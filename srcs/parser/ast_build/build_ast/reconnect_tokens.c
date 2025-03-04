/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconnect_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:48:10 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:09:48 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	reconnect_tokens(t_token *start, t_token *split)
{
	t_token	*prev;

	prev = start;
	while (prev->next != NULL)
		prev = prev->next;
	prev->next = split;
}
