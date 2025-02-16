/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env_var_declaration.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:05:05 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/16 18:05:19 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

int	is_env_var_declaration(const char *input, int *i)
{
	int	start;

	start = *i;
	if (!ft_isalpha(input[*i]) && input[*i] != '_')
		return (0);
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	if (input[*i] != '=')
	{
		*i = start;
		return (0);
	}
	(*i)++;
	if (!input[*i] || ft_isspace(input[*i]))
	{
		*i = start;
		return (0);
	}
	*i = start;
	return (1);
}
