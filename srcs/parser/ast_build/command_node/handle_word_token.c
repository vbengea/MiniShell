/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:36:36 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:10:39 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	handle_word_token(t_token *token, int *count, bool *prev_export)
{
	if (ft_strcmp(token->value, "export") == 0)
	{
		if (!*prev_export)
		{
			(*count)++;
			*prev_export = true;
		}
	}
	else
	{
		(*count)++;
		*prev_export = false;
	}
}
