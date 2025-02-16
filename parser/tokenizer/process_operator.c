/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:04:39 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/16 18:04:47 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_token	*process_operator(const char *input, int *i)
{
	t_token	*new_token;

	new_token = NULL;
	handle_operator(&new_token, NULL, input, i);
	return (new_token);
}
