/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:43:41 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/26 12:19:45 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node	*build_command_node(t_token *tokens)
{
	int		count;
	t_token	*current;
	char	**cmd_args;
	int		i;

	count = 0;
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
	i = 0;
	while (i < count && current && current->value)
	{
		cmd_args[i] = ft_strdup(current->value);
		current = current->next;
	}
	cmd_args[count] = NULL;
	return (create_ast_node(NODE_CMND, cmd_args));
}
