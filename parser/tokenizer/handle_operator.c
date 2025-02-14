/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:15:10 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/14 13:11:37 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

void	handle_operator(t_token **head, t_token *new_token, \
	const char *input, int *i)
{
	char	op;
	int		count;

	op = input[*i];
	count = count_consecutive_operators(input, i, op);
	dispatch_operator(head, new_token, op, count);
}
