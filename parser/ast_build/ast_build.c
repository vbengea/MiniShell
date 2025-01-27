/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:06:43 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/27 19:15:49 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

/**
 * @brief build an abstract syntax tree from a linked list of tokens
 * @param token linked list of tokens
 * @warning Mucho que limpiar ...
 */
t_ast_node	*build_ast(t_token *tokens)
{
	t_ast_node	*left;
	t_ast_node	*right;
	
	if (!tokens)
		return (NULL);

	// Handle parentheses
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

			// Create a group node
			t_ast_node *group_node = create_ast_node(NODE_GROUP, NULL);
			group_node->left = inner;

			// Continue processing the remaining tokens
			if (next_after_paren)
			{
				// Check if the next token is a valid operator
				if (next_after_paren->type != TOKEN_PIPE &&
					next_after_paren->type != TOKEN_AND &&
					next_after_paren->type != TOKEN_OR)
				{
					// Invalid syntax: report an error
					fprintf(stderr, "Syntax error: Expected an operator after ')'\n");
					return NULL; // Or handle the error as needed
				}

				// Determine the node type based on the next token
				t_ast_node *root = NULL;
				if (next_after_paren->type == TOKEN_PIPE)
					root = create_ast_node(NODE_PIPE, NULL);
				else if (next_after_paren->type == TOKEN_AND)
					root = create_ast_node(NODE_AND, NULL);
				else if (next_after_paren->type == TOKEN_OR)
					root = create_ast_node(NODE_OR, NULL);
				else
				{
					// This should never happen due to the check above
					fprintf(stderr, "Internal error: Unexpected token type after ')'\n");
					return NULL;
				}

				// Connect the group node and the remaining AST
				root->left = group_node;
				root->right = build_ast(next_after_paren);
				return root;
			}
			return group_node;
		}
	}

	// Handle operators and commands
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

void free_ast(t_ast_node *node)
{
	char	**cmd_args;
	int		i;

	if (!node)
		return;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_CMND || node->type == NODE_REDIRECT)
	{
		cmd_args = (char **)node->args;
		if (cmd_args)
		{
			i = 0;
			while (cmd_args[i])
			{
				free(cmd_args[i]);
				i++;
			}
			free(cmd_args);
		}
	}
	free(node);
}

void print_ast(t_ast_node *node, int level)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("Node type: %d", node->type);
	if (node->args)
	{
		printf(", args: ");
		for (int j = 0; node->args[j] != NULL; j++)
		{
			printf("%s ", node->args[j]);
		}
	}
	if (node->file)
	{
		printf(", file: %s", node->file);
	}
	printf("\n");
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}