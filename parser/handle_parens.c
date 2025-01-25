/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:16:24 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/25 13:22:56 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	handle_parens(t_token **head, t_token *new_token, char op, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (op == '(')
			new_token = create_token(TOKEN_OPEN_PAREN, "(");
		else
			new_token = create_token(TOKEN_CLOSE_PAREN, ")");
		add_token(head, new_token);
	}
}