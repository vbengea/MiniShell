/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirect_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea <vbengea@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:57:22 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/30 10:44:00 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

// t_ast_node	*create_redirect_node(t_token *token)
// {
// 	t_token	*temp;
// 	char	**cmd_args;

// 	temp = token->next;
// 	cmd_args = NULL;
// 	if (temp && temp->type == TOKEN_WORD)
// 	{
// 		cmd_args = malloc(sizeof(char *) * 2);
// 		cmd_args[0] = ft_strdup(temp->value);
// 		cmd_args[1] = NULL;
// 	}
// 	return (create_ast_node(NODE_REDIRECT, cmd_args));
// }


t_ast_node	*create_redirect_node(t_token *token)
{
	t_redirect_type	redirect_type;
	t_ast_node		*node;
	t_token			*file_token;

	if (!token || !is_redirect_token(token->type))
		return (NULL);
	if (token->type == TOKEN_REDIRECT_IN)
		redirect_type = REDIRECT_IN;
	else if (token->type == TOKEN_REDIRECT_OUT)
		redirect_type = REDIRECT_OUT;
	else if (token->type == TOKEN_APPEND)
		redirect_type = REDIRECT_APPEND;
	else if (token->type == TOKEN_HEREDOC)
		redirect_type = REDIRECT_HEREDOC;
	else
		return (NULL);
	node = create_ast_node(NODE_REDIRECT, NULL);
	if (!node)
		return (NULL);
	node->redirect_type = redirect_type;
	file_token = token->next;
	if (file_token && file_token->type == TOKEN_WORD)
	{
		node->file = ft_strdup(file_token->value);
		if (!node->file)
		{
			free (node);
			return (NULL);
		}
	}
	else
	{
		fprintf(stderr, "Syntax error: Expected a file after redirection operator\n");
		free (node);
		return (NULL);
	}
	return (node);
}