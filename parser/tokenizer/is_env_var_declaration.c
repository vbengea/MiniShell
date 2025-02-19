/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env_var_declaration.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:05:05 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 11:57:56 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

static bool	check_var_name(const char *input, int *i)
{
	if (!ft_isalpha(input[*i]) && input[*i] != '_')
		return (false);
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	return (true);
}

static bool	check_quoted_value(const char *input, int *i)
{
	(*i)++;
	while (input[*i] && input[*i] != '"')
		(*i)++;
	if (input[*i] == '"')
	{
		(*i)++;
		return (true);
	}
	return (false);
}

static bool	check_unquoted_value(const char *input, int *i)
{
	if (!input[*i] || ft_isspace(input[*i]))
		return (false);
	return (true);
}

static bool	check_var_value(const char *input, int *i, int start)
{
	if (input[*i] == '"')
	{
		if (!check_quoted_value(input, i))
		{
			*i = start;
			return (false);
		}
	}
	else if (!check_unquoted_value(input, i))
	{
		*i = start;
		return (false);
	}
	*i = start;
	return (true);
}

bool	is_env_var_declaration(const char *input, int *i)
{
	int	start;

	start = *i;
	if (!check_var_name(input, i))
		return (false);
	if (input[*i] != '=')
	{
		*i = start;
		return (false);
	}
	(*i)++;
	return (check_var_value(input, i, start));
}
