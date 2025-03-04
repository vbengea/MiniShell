/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_invalid_operator_token.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:48:30 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:12:44 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

t_token	*create_invalid_operator_token(const char *input, int *i)
{
	t_token	*new_token;
	char	invalid_op[3];
	int		j;

	j = 0;
	invalid_op[j++] = input[(*i)++];
	invalid_op[j++] = input[(*i)++];
	invalid_op[j] = '\0';
	new_token = create_token(TOKEN_INVALID, ft_strdup(invalid_op));
	return (new_token);
}
