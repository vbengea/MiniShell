/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:46:59 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 19:05:58 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

char	*get_prompt(t_terminal *tty)
{
	char	*host;
	char	*user;
	char	*user_host_prompt;
	char	*final_prompt;

	if (!tty)
		return (NULL);
	clean_existing_prompt(tty);
	user = get_user_host(&host);
	if (!user)
		return (NULL);
	user_host_prompt = create_base_prompt(user, host);
	if (!user_host_prompt)
		return (NULL);
	final_prompt = create_path_prompt(user_host_prompt);
	free(user_host_prompt);
	if (!final_prompt)
		return (NULL);
	tty->prompt = final_prompt;
	return (final_prompt);
}
