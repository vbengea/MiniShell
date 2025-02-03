/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:47:26 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/03 18:48:09 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

void add_redirection(t_ast_node *cmd_node, t_redirect_type type, t_out_redirect_type otype, char *file)
{
	t_redirection *new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return;

	new_redir->type = type;
	new_redir->otype = otype;
	new_redir->file = ft_strdup(file);
	new_redir->next = cmd_node->redirs;
	cmd_node->redirs = new_redir;
}