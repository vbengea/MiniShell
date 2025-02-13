/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:08 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/13 18:16:25 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*get_history_filepath(t_terminal *tty)
{
	char	*home;

	home = get_env("HOME", tty);
	if (!home)
		return (NULL);
	return (ft_strjoin(home, HISTORY_FILE));
}

void	load_history_from_file(t_terminal *tty)
{
	char	*history_path;
	char	*line;
	int		fd;
	size_t	len;
	int		count;

	history_path = get_history_filepath(tty);
	if (!history_path)
		return ;
	fd = open(history_path, O_RDONLY);
	if (fd < 0)
	{
		free(history_path);
		return ;
	}
	count = 0;
	line = get_next_line(fd);
	while (line && count < MAX_HISTORY_LINES)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		add_history(line);
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	free(history_path);
}

void	save_history_to_file(t_terminal *tty)
{
	char		*history_path;
	int			fd;
	HIST_ENTRY	**history;
	int			i;
	int			start;

	history_path = get_history_filepath(tty);
	if (!history_path)
		return ;
	fd = open(history_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(history_path);
		return ;
	}
	history = history_list();
	if (history)
	{
		i = 0;
		while (history[i])
			i++;

		if (i > MAX_HISTORY_LINES)
			start = i - MAX_HISTORY_LINES;
		else
			start = 0;
		while (start < i)
		{
			ft_putstr_fd(history[start]->line, fd);
			ft_putchar_fd('\n', fd);
			start++;
		}
	}
	close(fd);
	free(history_path);
}