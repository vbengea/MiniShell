/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_word_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:07:12 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/14 13:10:08 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_token	*create_word_token(const char *input, int *i)
{
	t_token	*new_token;
	int		start;
	int		len;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
		&& !is_operator(input[*i]) && !is_quote(input[*i]))
		(*i)++;
	len = *i - start;
	new_token = create_token(TOKEN_WORD, ft_strndup(input + start, len));
	if (ft_isspace(input[*i]))
		new_token->has_space = true;
	return (new_token);
}
