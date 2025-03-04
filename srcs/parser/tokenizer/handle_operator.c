/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:15:10 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:13:06 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	handle_operator(t_token **head, t_token *new_token, \
	const char *input, int *i)
{
	char	op;
	int		count;

	op = input[*i];
	count = count_consecutive_operators(input, i, op);
	dispatch_operator(head, new_token, op, count);
}
