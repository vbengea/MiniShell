/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_no_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea <vbengea@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:09:08 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/20 09:50:00 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

char	*handle_no_env(void)
{
	char	*line;
	int		fd;

	fd = open("/etc/environment", O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strnstr(line, "PATH=", 5) != NULL)
		{
			close(fd);
			return (line + 5);
		}
		free (line);
		line = get_next_line(fd);
	}
	close(fd);
	return (NULL);
}
