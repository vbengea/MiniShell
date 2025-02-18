/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history_from_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:49:34 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/18 18:54:44 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static void	read_from_file(t_history *myhist, char *line, int fd)
{
	size_t	len;

	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len -1] = '\0';
		if (myhist->count < MAX_HISTORY_LINES)
			add_to_both_histories(myhist, line);
		free(line);
		line = get_next_line(fd);
	}
}

void	load_history_from_file(t_history *myhist, t_terminal *tty)
{
	char	*history_path;
	char	*line;
	int		fd;

	history_path = get_history_filepath(tty);
	if (!history_path)
		return ;
	fd = open(history_path, O_RDONLY);
	if (fd < 0)
	{
		free(history_path);
		return ;
	}
	myhist->count = 0;
	line = get_next_line(fd);
	read_from_file(myhist, line, fd);
	close(fd);
	free(history_path);
}
