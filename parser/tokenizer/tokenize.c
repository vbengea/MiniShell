/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:18:54 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/08 20:03:02 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_token *tokenize(const char *input, int *i)
{
	t_token *head;
	t_token *new_token;

	head = NULL;
	new_token = NULL;
	while (input[*i])
	{
		skip_whitespace(input, i);
		if (isdigit(input[*i]) && (input[*i + 1] == '>' || input[*i + 1] == '<'))
		{
			new_token = create_fd_redirection_token(input, i);
			add_token(&head, new_token);
		}
		else if ((input[*i] == '<' || input[*i] == '>') && isdigit(input[*i + 1]))
		{
			// Handle cases like "<2" or ">2"
			new_token = create_invalid_operator_token(input, i);
			add_token(&head, new_token);
		}
		else if (is_operator(input[*i]))
		{
			handle_operator(&head, new_token, input, i);
		}
		else if (is_quote(input[*i]))
		{
			new_token = create_quoted_token(input, i);
			add_token(&head, new_token);
		}
		else
		{
			new_token = create_word_token(input, i);
			add_token(&head, new_token);
		}
	}
	return (head);
}

t_token	*tokenize_input(const char *input)
{
	int		i;

	i = 0;
	return (tokenize(input, &i));
}
