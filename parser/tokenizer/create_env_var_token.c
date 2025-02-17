/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_var_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:05:37 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/17 18:09:21 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

static int	find_env_var_name_end(const char *input, int start)
{
	int	i;

	i = start;
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	return (i);
}

static int	handle_quoted_value(const char *input, int *i)
{
	int	end;

	(*i)++;
	end = *i;
	while (input[end] && input[end] != '"')
		end++;
	if (input[end] == '"')
		end++;
	return (end);
}

static int	handle_unquoted_value(const char *input, int i)
{
	int	end;

	end = i;
	while (input[end] && !ft_isspace(input[end]) && !is_operator(input[end]))
		end++;
	return (end);
}

t_token	*create_env_var_token(const char *input, int *i)
{
	t_token	*token;
	int		start;
	int		end;

	start = *i;
	*i = find_env_var_name_end(input, start);
	if (input[*i] != '=')
	{
		*i = start;
		return (create_word_token(input, i));
	}
	(*i)++;
	if (input[*i] == '"')
		end = handle_quoted_value(input, i);
	else
		end = handle_unquoted_value(input, *i);
	token = create_token(TOKEN_ENV_VAR, ft_strndup(input + start, end - start));
	*i = end;
	return (token);
}
