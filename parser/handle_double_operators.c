/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:25:32 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/25 13:25:56 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	handle_double_operators(t_token **head, t_token *new_token, char op)
{
	if (op == '|')
		new_token = create_token(TOKEN_OR, "||");
	else if (op == '&')
		new_token = create_token(TOKEN_AND, "&&");
	else if (op == '<')
		new_token = create_token(TOKEN_HEREDOC, "<<");
	else if (op == '>')
		new_token = create_token(TOKEN_APPEND, ">>");
	else
		new_token = create_token(TOKEN_INVALID, "Invalid operator");
	add_token(head, new_token);
}
