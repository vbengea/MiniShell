/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:18:54 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/25 13:35:29 by vbengea          ###   ########.fr       */
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


void dispatch_operator(t_token **head, t_token *new_token, char op, int count)
{
	if (op == '(' || op == ')')
		handle_parens(head, new_token, op, count);
	else if (count == 2)
		handle_double_operators(head, new_token, op);
	else if (count == 1)
		handle_single_operator(head, new_token, op);
	else
	{
		new_token = create_token(TOKEN_INVALID, "Invalid operator");
		add_token(head, new_token);
	}
}

void handle_operator(t_token **head, t_token *new_token, const char *input, int *i)
{
	char op = input[*i];
	int count = count_consecutive_operators(input, i, op);
	dispatch_operator(head, new_token, op, count);
}

t_token *tokenize(const char *input, int *i)
{
	t_token	*head;
	t_token	*new_token;

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

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)env;
	(void)argv;
	t_token	*token;
	t_token	*tmp;

	while (true)
	{
		char *input = readline("minishell$ ");
		if (!input)
			break;
		token = tokenize_input(input);
		tmp = token;
		while (tmp)
		{
			printf("type: %d, value: %s\n", tmp->type, tmp->value);
			tmp = tmp->next;
		}
		free(input);
		free_token(token);
	}
	return (0);
}