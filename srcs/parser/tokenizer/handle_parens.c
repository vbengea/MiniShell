/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:16:24 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:13:09 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	handle_parens(t_token **head, t_token *new_token, char op, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (op == '(')
			new_token = create_token(TOKEN_OPEN_PAREN, ft_strdup("("));
		else
			new_token = create_token(TOKEN_CLOSE_PAREN, ft_strdup(")"));
		add_token(head, new_token);
		i++;
	}
}
