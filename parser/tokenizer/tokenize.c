/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:18:54 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/14 13:30:56 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_token	*process_token(const char *input, int *i)
{
	if (ft_isdigit(input[*i]) && (input[*i + 1] == '>' || input[*i + 1] == '<'))
		return (create_fd_redirection_token(input, i));
	else if ((input[*i] == '<' || input[*i] == '>')
		&& ft_isdigit(input[*i + 1]))
		return (create_invalid_operator_token(input, i));
	else if (is_operator(input[*i]))
		return (process_operator(input, i));
	else if (is_quote(input[*i]))
		return (create_quoted_token(input, i));
	else if (is_env_var_declaration(input, i))
		return (create_env_var_token(input, i));
	else
		return (create_word_token(input, i));
}

t_token	*process_operator(const char *input, int *i)
{
	t_token	*new_token;

	new_token = NULL;
	handle_operator(&new_token, NULL, input, i);
	return (new_token);
}

int	is_env_var_declaration(const char *input, int *i)
{
	int	start;

	start = *i;
	if (!ft_isalpha(input[*i]) && input[*i] != '_')
		return (0);
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	if (input[*i] != '=')
	{
		*i = start;
		return (0);
	}
	(*i)++;
	if (!input[*i] || ft_isspace(input[*i]))
	{
		*i = start;
		return (0);
	}
	*i = start;
	return (1);
}

t_token	*create_env_var_token(const char *input, int *i)
{
	t_token	*token;
	int		start;
	int		end;

	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	if (input[*i] != '=')
	{
		*i = start;
		return (create_word_token(input, i));
	}
	(*i)++;
	end = *i;
	while (input[end] && !ft_isspace(input[end]) && !is_operator(input[end]))
		end++;
	token = create_token(TOKEN_ENV_VAR, ft_strndup(input + start, end - start));
	*i = end;
	return (token);
}

t_token	*tokenize(const char *input, int *i)
{
	t_token	*head;
	t_token	*new_token;

	head = NULL;
	while (input[*i])
	{
		skip_whitespace(input, i);
		new_token = process_token(input, i);
		add_token(&head, new_token);
	}
	return (head);
}

t_token	*tokenize_input(const char *input)
{
	int		i;

	i = 0;
	return (tokenize(input, &i));
}
