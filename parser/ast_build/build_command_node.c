/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:43:41 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/28 19:36:39 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

t_ast_node	*build_command_node(t_token *tokens)
{
	char	**cmd_args;
	t_token	*current;
	int		count;
	int		i;

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
	return (create_ast_node(NODE_CMND, cmd_args));
}
