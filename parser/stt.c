/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:27:00 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/23 19:56:36 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

t_token	*create_token(t_token_tpype type, char *value);
void	add_token(t_token **head, t_token *new_token);

typedef enum e_state
{
	STATE_DEFAULT,
	STATE_WORD,
	STATE_PIPE,
	STATE_AND,
	STATE_OR,
	STATE_REDIRECT,
	STATE_SINGLE_QUOTE,
	STATE_DOUBLE_QUOTE
}	t_state;

static t_state handle_word_state(char c)
{
	if (ft_isspace(c))
		return (STATE_DEFAULT);
	if (c == '|')
		return (STATE_PIPE);
	if (c == '&')
		return (STATE_AND);
	if (c == ';')
		return (STATE_OR);
	if (c == '>')
		return (STATE_REDIRECT);
	if (c == '\'')
		return (STATE_SINGLE_QUOTE);
	if (c == '"')
		return (STATE_DOUBLE_QUOTE);
	return (STATE_WORD);
}

static t_state handle_quote_states(t_state current_state, char c)
{
	if (current_state == STATE_SINGLE_QUOTE)
		return (c == '\'' ? STATE_WORD : STATE_SINGLE_QUOTE);
	if (current_state == STATE_DOUBLE_QUOTE)
		return (c == '"' ? STATE_WORD : STATE_DOUBLE_QUOTE);
	return (STATE_WORD);
}

static t_state handle_operator_states(t_state current_state)
{
	if (current_state == STATE_PIPE || current_state == STATE_AND
		|| current_state == STATE_OR || current_state == STATE_REDIRECT)
		return (STATE_WORD);
	return (current_state);
}

t_state	get_next_state(t_state current_state, char c)
{
	if (current_state == STATE_WORD)
		return (handle_word_state(c));
	if (current_state == STATE_SINGLE_QUOTE
		|| current_state == STATE_DOUBLE_QUOTE)
		return (handle_quote_states(current_state, c));
	current_state = handle_operator_states(current_state);
	return (handle_word_state(c));
}


void	print_token(t_token *token)
{
	while (token)
	{
		printf("%s\n", token->value);
		token = token->next;
	}
}

// Same code, less lines

int parse_word(const char *input, int i, t_token **head)
{
	int start = i;
	while (input[i] && get_next_state(STATE_WORD, input[i]) == STATE_WORD)
		i++;
	t_token *tk = create_token(TOKEN_WORD, ft_strndup(&input[start], i - start));
	add_token(head, tk);
	return i;
}

int parse_pipe(const char *input, int i, t_token **head)
{
	(void)input;
	add_token(head, create_token(TOKEN_PIPE, ft_strdup("|")));
	return i + 1;
}

int parse_and(const char *input, int i, t_token **head)
{
	(void)input;
	add_token(head, create_token(TOKEN_AND, ft_strdup("&")));
	return i + 1;
}

int parse_or(const char *input, int i, t_token **head)
{
	(void)input;
	add_token(head, create_token(TOKEN_OR, ft_strdup(";")));
	return i + 1;
}

int parse_redirect(const char *input, int i, t_token **head)
{
	if (input[i + 1] == '>')
	{
		add_token(head, create_token(TOKEN_REDIRECT, ft_strdup(">>")));
		return i + 2;
	}
	add_token(head, create_token(TOKEN_REDIRECT, ft_strdup(">")));
	return i + 1;
}

int parse_single_quote(const char *input, int i, t_token **head)
{
	int start = ++i;
	while (input[i] && input[i] != '\'')
		i++;
	t_token *tk = create_token(TOKEN_WORD, ft_strndup(&input[start], i - start));
	add_token(head, tk);
	if (input[i]) i++;
	return i;
}

int parse_double_quote(const char *input, int i, t_token **head)
{
	int start = ++i;
	while (input[i] && input[i] != '"')
		i++;
	t_token *tk = create_token(TOKEN_WORD, ft_strndup(&input[start], i - start));
	add_token(head, tk);
	if (input[i]) i++;
	return i;
}

static int handle_default_state(t_state state, int i)
{
	if (state == STATE_DEFAULT)
	{
		i++;
		return (1);
	}
	return (0);
}

static int a_parse_token(t_state state, const char *input, int i, t_token **head)
{
	if (state == STATE_WORD)
		return (parse_word(input, i, head));
	else if (state == STATE_PIPE)
		return (parse_pipe(input, i, head));
	else if (state == STATE_AND)
		return (parse_and(input, i, head));
	else if (state == STATE_OR)
		return (parse_or(input, i, head));
	else if (state == STATE_REDIRECT)
		return (parse_redirect(input, i, head));
	else if (state == STATE_SINGLE_QUOTE)
		return (parse_single_quote(input, i, head));
	return (parse_double_quote(input, i, head));
}

t_token *tokenize(const char *input)
{
	t_token *head;
	int i;
	t_state state;

	head = NULL;
	i = 0;
	state = STATE_DEFAULT;
	while (input[i])
	{
		state = get_next_state(state, input[i]);
		if (handle_default_state(state, i))
			continue ;
		i = a_parse_token(state, input, i, &head);
	}
	return (head);
}


int main(void)
{
	t_token	*token;

	token = tokenize("ls -l | grep \"test\" > file");
	print_token(token);
}