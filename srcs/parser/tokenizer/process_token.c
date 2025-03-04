/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:03:49 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:13:35 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

t_token	*process_token(const char *input, int *i)
{
	if (ft_isdigit(input[*i]) && (input[*i + 1] == '>' || input[*i + 1] == '<'))
		return (create_fd_redirection_token(input, i));
	else if ((input[*i] == '<' || input[*i] == '>')
		&& ft_isdigit(input[*i + 1]))
		return (create_invalid_operator_token(input, i));
	else if (is_operator(input[*i]))
		return (process_operator(input, i));
	else if (is_env_var_declaration(input, i))
		return (create_env_var_token(input, i));
	else if (is_quote(input[*i]))
		return (create_quoted_token(input, i));
	else
		return (create_word_token(input, i));
}
