/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_invalid_operator_token.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:48:30 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/02 19:48:59 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_token *create_invalid_operator_token(const char *input, int *i)
{
	t_token *new_token;
	char invalid_op[3]; // Enough space for "<2", ">2", etc.
	int j = 0;

	// Capture the operator and the following digit
	invalid_op[j++] = input[(*i)++];
	invalid_op[j++] = input[(*i)++];
	invalid_op[j] = '\0';

	// Create an invalid token
	new_token = create_token(TOKEN_INVALID, strdup(invalid_op));
	return new_token;
}