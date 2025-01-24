/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:18:54 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/24 19:42:44 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	skip_whitespace(const char *input, int *i)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
}

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == ';' || c == '(' || c == ')');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

void handle_operator(t_token **head, t_token *new_token, const char *input, int *i)
{
	int  count;
	char op;

	op = input[*i];
	count = 0;
	while (input[*i] == op)
	{
		count++;
		(*i)++;
	}
	if (count == 2)
	{
		if (op == '|')
			new_token = create_token(TOKEN_OR, "||");
		else if (op == '&')
			new_token = create_token(TOKEN_AND, "&&");
		else if (op == '<')
			new_token = create_token(TOKEN_HEREDOC, "<<");
		else if (op == '>')
			new_token = create_token(TOKEN_APPEND, ">>");
		else
			new_token = create_token(TOKEN_INVALID, "Invalid operator");
	}
	else if (count == 1)
	{
		if (op == '|')
			new_token = create_token(TOKEN_PIPE, "|");
		else if (op == '<')
			new_token = create_token(TOKEN_REDIRECT_IN, "<");
		else if (op == '>')
			new_token = create_token(TOKEN_REDIRECT_OUT, ">");
		else if (op == '&')
			new_token = create_token(TOKEN_BG, "&");
		else if (op == '(')
			new_token = create_token(TOKEN_OPEN_PAREN, "(");
		else if (op == ')')
			new_token = create_token(TOKEN_CLOSE_PAREN, ")");
		else
			new_token = create_token(TOKEN_INVALID, "Invalid operator");
	}
	else
	{
		new_token = create_token(TOKEN_INVALID, "Invalid operator");
	}
	add_token(head, new_token);
}


t_token *tokenize(const char *input, int *i)
{
	t_token	*head;
	t_token	*new_token;
	// char	*temp;

	head = NULL;
	while (input[*i])
	{
		skip_whitespace(input, i);
		if (is_operator(input[*i]))
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

int main(int argc, char **argv)
{
	(void)argc;
	t_token	*token;
	t_token	*tmp;

	token = tokenize_input(argv[1]);
	tmp = token;
	while (tmp)
	{
		printf("type: %d, value: %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}