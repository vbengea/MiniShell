/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:00:44 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/07 12:39:21 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

void	update_paren_level(int *level, t_token_type type)
{
	if (type == TOKEN_OPEN_PAREN)
		(*level)++;
	else if (type == TOKEN_CLOSE_PAREN)
		(*level)--;
}

void	update_split_point(t_token **split, t_token *current, int *min_prec)
{
	if ((current->type == TOKEN_AND
		|| current->type == TOKEN_OR) && *min_prec >= 1)
	{
		*min_prec = 1;
		*split = current;
	}
	else if (current->type == TOKEN_PIPE && *min_prec >= 2)
	{
		*min_prec = 2;
		*split = current;
	}
	else if (is_redirect_token(current->type) && *min_prec >= 3)
	{
		*min_prec = 3;
		*split = current;
	}
}

int	count_word_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current && current->type == TOKEN_WORD)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	disconnect_tokens(t_token *start, t_token *split)
{
	t_token	*prev;

	prev = start;
	while (prev->next != split)
		prev = prev->next;
	prev->next = NULL;
}


void	reconnect_tokens(t_token *start, t_token *split)
{
	t_token	*prev;

	prev = start;
	while (prev->next != NULL)
		prev = prev->next;
	prev->next = split;
}

int	is_valid_operator(t_token_type type)
{
	return (type == TOKEN_PIPE ||
			type == TOKEN_AND ||
			type == TOKEN_OR);
}


t_ast_node *build_ast(t_token *tokens)
{
	t_token *split_point;
	t_ast_node *left;

	if (!tokens)
		return (NULL);

	// Handle parentheses
	if (tokens->type == TOKEN_OPEN_PAREN)
		return (handle_parentheses(tokens));

	// Find the split point (lowest precedence operator)
	split_point = find_split_point(tokens);
	if (!split_point)
	{
		// printf("No split point found, building command node\n");
		return (build_command_node(tokens));
	}

	// printf("Split point found: type=%d, value=%s\n", split_point->type, split_point->value);

	// Build the left subtree
	left = NULL;
	if (split_point != tokens)
	{
		// printf("Building left subtree\n");
		disconnect_tokens(tokens, split_point);
		left = build_ast(tokens);
		reconnect_tokens(tokens, split_point);
	}

	// printf("Building operator node\n");
	return (build_operator_node(left, split_point));
}