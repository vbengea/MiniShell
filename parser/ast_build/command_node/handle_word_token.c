/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea <vbengea@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:36:36 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/18 08:25:36 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"

void	handle_word_token(t_token *temp, int *count, bool *prev_export)
{
	(*count)++;
	*prev_export = (temp->value && ft_strcmp(temp->value, "export") == 0);
}
