/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:04:39 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:13:32 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

t_token	*process_operator(const char *input, int *i)
{
	t_token	*new_token;

	new_token = NULL;
	if (input[*i] == '(' || input[*i] == ')')
	{
		handle_parens(&new_token, new_token, input[*i], 1);
		(*i)++;
	}
	else
		handle_operator(&new_token, NULL, input, i);
	return (new_token);
}
