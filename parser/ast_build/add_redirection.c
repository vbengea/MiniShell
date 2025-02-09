/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea <vbengea@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:47:26 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/05 11:55:07 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

void add_redirection(t_ast_node *node, t_redirect_type type, t_out_redirect_type otype, char *file)
{
	t_redirection *new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return;

	new_redir->type = type;
	new_redir->otype = otype;
	new_redir->file = file;
	new_redir->next = NULL;

	if (!node->redirs)
	{
		node->redirs = new_redir;
	}
	else
	{
		t_redirection *current = node->redirs;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}