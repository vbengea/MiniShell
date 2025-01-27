/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea <vbengea@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:06:43 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/27 12:41:40 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node	*build_ast(t_token *tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	
	if (!tokens)
		return (NULL);

	if (tokens->type == TOKEN_OPEN_PAREN)
	{
		int paren_count = 1;
		t_token *end = tokens->next;
		
		while (end && paren_count > 0)
		{			
			if (end->type == TOKEN_OPEN_PAREN)
				paren_count++;
			else if (end->type == TOKEN_CLOSE_PAREN)
				paren_count--;
			if (paren_count > 0)
				end = end->next;
		}
		
		if (end && paren_count == 0)
		{
			t_token *next_after_paren = end->next;
			end->next = NULL;
			t_ast_node *inner = build_ast(tokens->next);
			end->next = next_after_paren;


			// NODE_GROUP
			t_ast_node *group_node = create_ast_node(NODE_GROUP, NULL);
			group_node->left = inner;
			group_node->right = NULL;


			if (next_after_paren)
				return build_ast_with_inner(inner, next_after_paren);
			//return inner;
			return group_node;
		}
	}

	t_token *current = tokens;
	t_token *split_point = NULL;
	int min_precedence = 100;
	int paren_level = 0;

	while (current)
	{
		if (current->type == TOKEN_OPEN_PAREN)
			paren_level++;
		else if (current->type == TOKEN_CLOSE_PAREN)
			paren_level--;
		
		if (paren_level == 0)
		{
			if (current->type == TOKEN_AND || current->type == TOKEN_OR)
			{
				if (min_precedence >= 1)
				{
					min_precedence = 1;
					split_point = current;
				}
			}
			else if (current->type == TOKEN_PIPE)
			{
				if (min_precedence >= 2)
				{
					min_precedence = 2;
					split_point = current;
				}
			}
			else if (current->type == TOKEN_REDIRECT_IN || 
					current->type == TOKEN_REDIRECT_OUT || 
					current->type == TOKEN_APPEND)
			{
				if (min_precedence >= 3)
				{
					min_precedence = 3;
					split_point = current;
				}
			}
		}
		current = current->next;
	}
	if (!split_point)
	{
		char **cmd_args = NULL;
		int count = 0;

		current = tokens;
		while (current && current->type == TOKEN_WORD)
		{
			count++;
			current = current->next;
		}

		cmd_args = malloc(sizeof(char *) * (count + 1));
		if (!cmd_args)
			return (NULL);
		current = tokens;
		int i = 0;
		while (i < count)
		{
			cmd_args[i] = ft_strdup(current->value);
			current = current->next;
			i++;
		}
		cmd_args[i] = NULL;
		return (create_ast_node(NODE_CMND, cmd_args));
	}
	else
	{
		t_token *temp = split_point->next;

		left = NULL;
		if (split_point != tokens)
		{
			t_token *prev = tokens;
			while (prev->next != split_point)
				prev = prev->next;
			prev->next = NULL;
			left = build_ast(tokens);
			prev->next = split_point;
		}
		right = NULL;
		if (temp)
			right = build_ast(temp);
	}

	t_ast_node *root;

	if (split_point->type == TOKEN_PIPE)
		root = create_ast_node(NODE_PIPE, NULL);
	else if (split_point->type == TOKEN_AND)
		root = create_ast_node(NODE_AND, NULL);
	else if (split_point->type == TOKEN_OR)
		root = create_ast_node(NODE_OR, NULL);
	else if (split_point->type == TOKEN_REDIRECT_IN
			|| split_point->type == TOKEN_REDIRECT_OUT
			|| split_point->type == TOKEN_APPEND)
	{
		t_token *temp = split_point->next;
		char **cmd_args = NULL;
		if (temp && temp->type == TOKEN_WORD)
		{
			cmd_args = malloc(sizeof(char *) * 2);
			cmd_args[0] = ft_strdup(temp->value);
			cmd_args[1] = NULL;
		}
		root = create_ast_node(NODE_REDIRECT, cmd_args);
	}
	else if (split_point->type == TOKEN_APPEND)
		root = create_ast_node(NODE_REDIRECT, NULL);
	else
		return (NULL);
	root->left = left;
	root->right = right;

	return (root);
}

