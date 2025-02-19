/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:31:38 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 20:06:28 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"

int	handle_redirection(t_ast_node *node, t_token **current)
{
	t_redirection_info	redir_info;
	t_token				*next;

	redir_info.otype = STDOUT_FILE;
	redir_info.type = get_redirect_type((*current)->type);
	next = (*current)->next;
	if (!next || next->type != TOKEN_WORD)
		return (0);
	*current = next;
	redir_info.file = ft_strdup((*current)->value);
	redir_info.quote_flag = (*current)->is_quoted;
	add_redirection(node, &redir_info);
	return (1);
}
