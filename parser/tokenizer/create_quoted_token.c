/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_quoted_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:42:26 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/29 18:06:25 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_token *create_quoted_token(const char *input, int *i)
{
	t_token	*new_token;
	char	*temp;
	char	quote;

	quote = input[*i];
	new_token = create_token(TOKEN_WORD, "");
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		temp = malloc(ft_strlen(new_token->value) + 2);
		ft_strcpy(temp, new_token->value);
		temp[ft_strlen(new_token->value)] = input[*i];
		temp[ft_strlen(new_token->value) + 1] = '\0';
		free(new_token->value);
		new_token->value = temp;
		(*i)++;
	}
	(*i)++;
	return (new_token);
}
