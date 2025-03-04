/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:47:26 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:10:52 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	add_redirection(t_ast_node *node, t_redirection_info *redir_info)
{
	t_redirection	*new_redir;
	t_redirection	*current;

	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return ;
	new_redir->is_quote = redir_info->quote_flag;
	new_redir->type = redir_info->type;
	new_redir->otype = redir_info->otype;
	new_redir->file = redir_info->file;
	new_redir->next = NULL;
	if (!node->redirs)
		node->redirs = new_redir;
	else
	{
		current = node->redirs;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}
