/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:18:54 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:13:47 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

t_token	*tokenize(const char *input, int *i)
{
	t_token	*head;
	t_token	*new_token;

	head = NULL;
	while (input[*i])
	{
		skip_whitespace(input, i);
		new_token = process_token(input, i);
		add_token(&head, new_token);
	}
	return (head);
}
