/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:08:50 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/24 19:09:38 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!head || !new_token)
		return ;
	tmp = *head;
	if (!tmp)
	{
		*head = new_token;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}
