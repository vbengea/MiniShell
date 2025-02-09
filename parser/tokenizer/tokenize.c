/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:18:54 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/09 11:54:06 by vbengea          ###   ########.fr       */
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
		if (ft_isdigit(input[*i]) && (input[*i + 1] == '>' || input[*i + 1] == '<'))
		{
			new_token = create_fd_redirection_token(input, i);
			add_token(&head, new_token);
		}
		else if ((input[*i] == '<' || input[*i] == '>') && ft_isdigit(input[*i + 1]))
		{
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
		else if (is_env_var_declaration(input, i))
		{
			new_token = create_env_var_token(input, i);
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

int is_env_var_declaration(const char *input, int *i)
{
	int start = *i;

	if (!ft_isalpha(input[*i]) && input[*i] != '_')
		return 0;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	if (input[*i] != '=')
	{
		*i = start;
		return 0;
	}
	(*i)++;
	if (!input[*i] || ft_isspace(input[*i]))
	{
		*i = start;
		return 0;
	}
	*i = start;
	return 1;
}


t_token *create_env_var_token(const char *input, int *i)
{
	t_token *token;
	int start = *i;
	int end;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	if (input[*i] != '=')
	{
		*i = start;
		return create_word_token(input, i);
	}
	(*i)++;
	end = *i;
	while (input[end] && !ft_isspace(input[end]) && !is_operator(input[end]))
		end++;
	token = create_token(TOKEN_ENV_VAR, ft_strndup(input + start, end - start));
	*i = end;
	return (token);
}



t_token	*tokenize_input(const char *input)
{
	int		i;

	i = 0;
	return (tokenize(input, &i));
}
