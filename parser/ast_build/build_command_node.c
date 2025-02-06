/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea <vbengea@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:43:41 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/05 11:57:51 by vbengea          ###   ########.fr       */
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

	count = count_word_tokens(tokens);
	cmd_args = malloc(sizeof(char *) * (count + 1));
	if (!cmd_args)
		return (NULL);

	current = tokens;
	i = 0;
	while (i < count)
	{
		cmd_args[i] = ft_strdup(current->value);
		current = current->next;
		i++;
	}
	cmd_args[i] = NULL;

	node = create_ast_node(NODE_CMND, cmd_args);

	// for (int j = 0; cmd_args[j]; j++)
	// 	printf("%s ", cmd_args[j]);
	// printf("\n");

	while (current && is_redirect_token(current->type))
	{
		t_redirect_type redirect_type;
		t_out_redirect_type otype = STDOUT_FILE;
		char *file = NULL;

		if (current->type == TOKEN_REDIRECT_IN)
			redirect_type = REDIRECT_IN;
		else if (current->type == TOKEN_REDIRECT_OUT)
			redirect_type = REDIRECT_OUT;
		else if (current->type == TOKEN_APPEND)
			redirect_type = REDIRECT_APPEND;
		else if (current->type == TOKEN_HEREDOC)
			redirect_type = REDIRECT_HEREDOC;

		current = current->next;
		if (current && current->type == TOKEN_WORD)
		{
			file = ft_strdup(current->value);
			current = current->next;
		}
		else
		{
			fprintf(stderr, "Syntax error: Expected a file after redirection operator\n");
			// free_ast(node);
			return (NULL);
		}

		add_redirection(node, redirect_type, otype, file);
	}

	return (node);
}