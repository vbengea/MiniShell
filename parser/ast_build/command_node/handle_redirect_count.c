/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect_count.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:35:45 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/15 21:15:13 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"

bool	handle_redirect_count(t_token **temp)
{
	*temp = (*temp)->next;
	if (!temp || (*temp)->type != TOKEN_WORD)
		return (false);
	return (true);
}
