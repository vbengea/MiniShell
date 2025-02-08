/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:43:41 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/08 11:15:04 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

int	count_command_words(t_token *tokens)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = tokens;
	while (temp)
	{
		if (temp->type == TOKEN_WORD)
			count++;
		else if (is_redirect_token(temp->type))
		{
			temp = temp->next;
			if (!temp || temp->type != TOKEN_WORD)
				return (-1);
		}
		temp = temp->next;
	}
	return (count);
}

char	**allocate_cmd_args(int count)
{
	char	**cmd_args;

	cmd_args = malloc(sizeof(char *) * (count + 1));
	if (!cmd_args)
		return (NULL);
	return (cmd_args);
}

t_redirect_type	get_redirect_type(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN)
		return (REDIRECT_IN);
	if (type == TOKEN_REDIRECT_OUT)
		return (REDIRECT_OUT);
	if (type == TOKEN_APPEND)
		return (REDIRECT_APPEND);
	return (REDIRECT_HEREDOC);
}

int	handle_redirection(t_ast_node *node, t_token **current)
{
	t_redirect_type		rtype;
	t_out_redirect_type	otype;
	t_token				*next;

	otype = STDOUT_FILE;
	rtype = get_redirect_type((*current)->type);
	next = (*current)->next;
	if (!next || next->type != TOKEN_WORD)
		return (0);
	*current = next;
	add_redirection(node, rtype, otype, ft_strdup((*current)->value));
	return (1);
}

int	fill_cmd_args(t_token *tokens, char **cmd_args, t_ast_node *node)
{
	t_token	*current;
	int		i;

	i = 0;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			cmd_args[i] = ft_strdup(current->value);
			i++;
		}
		else if (is_redirect_token(current->type))
		{
			if (!handle_redirection(node, &current))
				return (0);
		}
		current = current->next;
	}
	cmd_args[i] = NULL;
	return (1);
}

t_ast_node	*build_command_node(t_token *tokens)
{
	t_ast_node	*node;
	char		**cmd_args;
	int			count;

	node = create_ast_node(NODE_CMND, NULL);
	if (!node)
		return (NULL);
	count = count_command_words(tokens);
	if (count < 0)
		return (NULL);
	cmd_args = allocate_cmd_args(count);
	if (!cmd_args)
		return (NULL);
	if (!fill_cmd_args(tokens, cmd_args, node))
		return (NULL);
	node->args = cmd_args;
	return (node);
}
