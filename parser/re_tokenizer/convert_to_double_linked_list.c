/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_double_linked_list.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:19:47 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/01 13:28:23 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

static t_re_token	*create_new_node(t_token_type type, char *value)
{
	t_re_token	*new_node;

	new_node = malloc(sizeof(t_re_token));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->value = value;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_re_token	*convert_to_double_linked_list(t_token *tokens)
{
	t_re_token	*new_head;
	t_re_token	*prev_node;
	t_re_token	*new_node;
	t_token		*next_node;
	t_token		*current;

	current = tokens;
	prev_node = NULL;
	new_head = NULL;
	while (current)
	{
		new_node = create_new_node(current->type, current->value);
		if (prev_node)
			prev_node->next = new_node;
		else
			new_head = new_node;
		prev_node = new_node;
		next_node = current->next;
		free (current);
		current = next_node;
	}
	return (new_head);
}
