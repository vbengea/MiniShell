/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:08 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/13 20:25:56 by jflores          ###   ########.fr       */
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

void	init_local_history(t_history *myhist)
{
	int	i;

	myhist->count = 0;
	i = 0;
	while (i < MAX_HISTORY_LINES)
	{
		myhist->commands[i] = NULL;
		i++;
	}
}

void add_to_both_histories(t_history *myhist, const char *line)
{
	int	i;

	add_history(line);
	if (myhist->count < MAX_HISTORY_LINES)
	{
		myhist->commands[myhist->count] = ft_strdup(line);
		myhist->count++;
	}
	else
	{
		free(myhist->commands[0]);
		i = 1;
		while (i < MAX_HISTORY_LINES)
		{
			myhist->commands[i - 1] = myhist->commands[i];
			i++;
		}
		myhist->commands[MAX_HISTORY_LINES - 1] = ft_strdup(line);
	}
}

void	load_history_from_file(t_history *myhist, t_terminal *tty)
{
	char	*history_path;
	char	*line;
	int		fd;
	size_t	len;

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
	while (line && myhist->count < MAX_HISTORY_LINES)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		add_to_both_histories(myhist, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(history_path);
}

void	save_history_to_file(t_history *myhist, t_terminal *tty)
{
	char	*history_path;
	int		fd;
	int		i;

	history_path = get_history_filepath(tty);
	if (!history_path)
		return ;
	fd = open(history_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(history_path);
		return ;
	}
	i = 0;
	while (i < myhist->count)
	{
		if (myhist->commands[i])
		{
			ft_putstr_fd(myhist->commands[i], fd);
			ft_putchar_fd('\n', fd);
			free (myhist->commands[i]);
		}
		i++;
	}
	close(fd);
	free(history_path);
}
