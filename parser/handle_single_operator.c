/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_operator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:27:16 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/25 13:28:16 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	handle_single_operator(t_token **head, t_token *new_token, char op)
{
	if (op == '|')
		new_token = create_token(TOKEN_PIPE, "|");
	else if (op == '<')
		new_token = create_token(TOKEN_REDIRECT_IN, "<");
	else if (op == '>')
		new_token = create_token(TOKEN_REDIRECT_OUT, ">");
	else if (op == '&')
		new_token = create_token(TOKEN_BG, "&");
	else if (op == ';')
		new_token = create_token(TOKEN_INVALID, "Invalid operator");
	add_token(head, new_token);
}
