/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirect_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:57:22 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/28 18:18:50 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node	*create_redirect_node(t_token *token)
{
	t_token	*temp;
	char	**cmd_args;

	temp = token->next;
	cmd_args = NULL;
	if (temp && temp->type == TOKEN_WORD)
	{
		cmd_args = malloc(sizeof(char *) * 2);
		cmd_args[0] = ft_strdup(temp->value);
		cmd_args[1] = NULL;
	}
	return (create_ast_node(NODE_REDIRECT, cmd_args));
}
