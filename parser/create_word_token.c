/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_word_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:07:12 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/24 19:16:34 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

t_token	*create_word_token(const char *input, int *i)
{
	t_token	*new_token;
	char	*temp;

	new_token = create_token(TOKEN_WORD, "");
	while (input[*i] && !is_operator(input[*i]) && !ft_isspace(input[*i]))
	{
		temp = malloc(ft_strlen(new_token->value) + 2);
		ft_strcpy(temp, new_token->value);
		temp[ft_strlen(new_token->value)] = input[*i];
		temp[ft_strlen(new_token->value) + 1] = '\0';
		free(new_token->value);
		new_token->value = temp;
		(*i)++;
	}
	return (new_token);
}
