/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_quoted_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:42:26 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/14 14:05:45 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

static int	get_quoted_length(const char *input)
{
	int		len;
	char	quote;

	quote = input[0];
	len = 0;
	input++;
	while (input[len] && input[len] != quote)
		len++;
	return (len);
}

static t_token	*init_quoted_token(int len)
{
	t_token	*new_token;

	new_token = create_token(TOKEN_WORD, NULL);
	if (!new_token)
		return (NULL);
	new_token->value = malloc(len + 1);
	if (!new_token->value)
	{
		free (new_token);
		return (NULL);
	}
	return (new_token);
}

static void	fill_token_content(t_token *token, const char *input, \
	int *i, char quote)
{
	int	j;

	j = 0;
	(*i)++;
	while (input[*i] && input[*i] != quote)
		token->value[j++] = input[(*i)++];
	token->value[j] = '\0';
}

static void	set_token_attributes(t_token *token, const char *input, \
	int *i, char quote)
{
	token->is_quoted = true;
	token->has_env = (quote != '\'');
	if (input[*i] == '\0')
		token->type = TOKEN_INVALID;
	else
	{
		token->has_space = ft_isspace(input[*i + 1]);
		(*i)++;
	}
}

t_token	*create_quoted_token(const char *input, int *i)
{
	t_token	*new_token;
	char	quote;
	int		len;

	quote = input[*i];
	len = get_quoted_length(input + *i);
	new_token = init_quoted_token(len);
	if (!new_token)
		return (NULL);
	fill_token_content(new_token, input, i, quote);
	set_token_attributes(new_token, input, i, quote);
	return (new_token);
}
