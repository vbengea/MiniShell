/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:25:32 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:13:03 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	handle_double_operators(t_token **head, t_token *new_token, char op)
{
	if (op == '|')
		new_token = create_token(TOKEN_OR, ft_strdup("||"));
	else if (op == '&')
		new_token = create_token(TOKEN_AND, ft_strdup("&&"));
	else if (op == '<')
		new_token = create_token(TOKEN_HEREDOC, ft_strdup("<<"));
	else if (op == '>')
		new_token = create_token(TOKEN_APPEND, ft_strdup(">>"));
	else
		new_token = create_token(TOKEN_INVALID, ft_strdup("Invalid operator"));
	add_token(head, new_token);
}
