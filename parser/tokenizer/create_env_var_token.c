/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_var_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:05:37 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/16 18:06:19 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_token	*create_env_var_token(const char *input, int *i)
{
	t_token	*token;
	int		start;
	int		end;

	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	if (input[*i] != '=')
	{
		*i = start;
		return (create_word_token(input, i));
	}
	(*i)++;
	end = *i;
	while (input[end] && !ft_isspace(input[end]) && !is_operator(input[end]))
		end++;
	token = create_token(TOKEN_ENV_VAR, ft_strndup(input + start, end - start));
	*i = end;
	return (token);
}
