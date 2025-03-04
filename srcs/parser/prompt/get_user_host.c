/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_host.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:49:01 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:12:00 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

char	*get_user_host(char **host_ptr)
{
	char	*user;
	char	*host;

	host = get_hostname();
	if (!host)
		return (NULL);
	*host_ptr = host;
	user = get_username();
	if (!user)
	{
		free(host);
		return (NULL);
	}
	return (user);
}
