/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:48:34 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/15 20:48:47 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"

void	disconnect_tokens(t_token *start, t_token *split)
{
	t_token	*prev;

	prev = start;
	while (prev->next != split)
		prev = prev->next;
	prev->next = NULL;
}
