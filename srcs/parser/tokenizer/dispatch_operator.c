/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:13:44 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:12:57 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	dispatch_operator(t_token **head, t_token *new_token, \
		char op, int count)
{
	if (op == '(' || op == ')')
		handle_parens(head, new_token, op, count);
	else if (count == 2)
		handle_double_operators(head, new_token, op);
	else if (count == 1)
		handle_single_operator(head, new_token, op);
	else
	{
		new_token = create_token(TOKEN_INVALID, ft_strdup("Invalid operator"));
		add_token(head, new_token);
	}
}
