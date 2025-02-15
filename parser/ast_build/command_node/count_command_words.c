/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_command_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:35:13 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/15 20:35:38 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"

int count_command_words(t_token *tokens)
{
	bool prev_export;
	t_token *temp;
	int count;

	count = 0;
	prev_export = false;
	temp = tokens;
	while (temp)
	{
		if (temp->type == TOKEN_WORD)
			handle_word_token(temp, &count, &prev_export);
		else if (temp->type == TOKEN_ENV_VAR)
			prev_export = handle_env_var_token(prev_export, &count);
		else if (is_redirect_token(temp->type))
		{
			if (!handle_redirect_count(&temp))
				return (-1);
		}
		temp = temp->next;
	}
	return (count);
}
