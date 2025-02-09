/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_quoted_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:42:26 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/09 12:45:34 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_token	*create_quoted_token(const char *input, int *i)
{
	t_token	*new_token;
	char	*temp;
	char	quote;

	quote = input[*i];
	new_token = create_token(TOKEN_WORD, ft_strdup(""));
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		if (quote == '"' && input[*i] == '$' && input[*i + 1] && (ft_isalpha(input[*i + 1]) || input[*i + 1] == '?'))
			new_token->has_env = true;
		temp = malloc(ft_strlen(new_token->value) + 2);
		ft_strcpy(temp, new_token->value);
		temp[ft_strlen(new_token->value)] = input[*i];
		temp[ft_strlen(new_token->value) + 1] = '\0';
		free(new_token->value);
		new_token->value = temp;
		(*i)++;
	}
	if (input[*i] == '\0')
		new_token->type = TOKEN_INVALID;
	else
		(*i)++;
	return (new_token);
}


// Check later this function for possible memory leaks
// Maybe here happens an invalid free