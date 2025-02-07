/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:43:41 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/07 12:38:03 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node *build_command_node(t_token *tokens)
{
	char **cmd_args;
	t_token *current;
	int count;
	int i;
	t_ast_node *node;

	// Create the command node
	node = create_ast_node(NODE_CMND, NULL);
	if (!node)
		return (NULL);

	// 1) First, count command words (ignoring redirections):
	count = 0;
	t_token *tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
			count++;
		else if (is_redirect_token(tmp->type))
		{
			tmp = tmp->next; // Skip the redirection operator
			if (!tmp || tmp->type != TOKEN_WORD)
				return NULL; // Syntax error
		}
		tmp = tmp->next;
	}

	// 2) Allocate memory for cmd_args:
	cmd_args = malloc(sizeof(char *) * (count + 1));
	if (!cmd_args)
		return NULL;

	// 3) Loop again to fill cmd_args and add redirections:
	current = tokens;
	i = 0;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			cmd_args[i++] = ft_strdup(current->value);
		}
		else if (is_redirect_token(current->type))
		{
			t_redirect_type redirect_type;
			t_out_redirect_type otype = STDOUT_FILE; // Default
			if (current->type == TOKEN_REDIRECT_IN)
				redirect_type = REDIRECT_IN;
			else if (current->type == TOKEN_REDIRECT_OUT)
				redirect_type = REDIRECT_OUT;
			else if (current->type == TOKEN_APPEND)
				redirect_type = REDIRECT_APPEND;
			else
				redirect_type = REDIRECT_HEREDOC;

			// Move past the operator and get the file token
			current = current->next;
			if (!current || current->type != TOKEN_WORD)
				return NULL; // Syntax error

			add_redirection(node, redirect_type, otype, ft_strdup(current->value));
		}
		if (current)
			current = current->next;
	}
	cmd_args[i] = NULL;
	node->args = cmd_args;

	return (node);
}