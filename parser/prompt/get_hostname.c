/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hostname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:40:12 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 19:03:12 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

char	*get_hostname(void)
{
	char	*host;
	int		host_fd;

	host_fd = open("/etc/hostname", O_RDONLY);
	if (host_fd < 0)
		host = ft_strdup("minishell");
	else
	{
		host = get_next_line(host_fd);
		if (host)
			host[ft_strlen(host) - 1] = '\0';
		close(host_fd);
		if (!host)
			host = ft_strdup("minishell");
	}
	return (host);
}
