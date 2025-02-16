/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history_to_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:50:06 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/16 18:56:59 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static void	write_to_file(t_history *myhist, int fd)
{
	int	i;

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
}

void	save_history_to_file(t_history *myhist, t_terminal *tty)
{
	char	*history_path;
	int		fd;

	history_path = get_history_filepath(tty);
	if (!history_path)
		return ;
	fd = open(history_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(history_path);
		return ;
	}
	write_to_file(myhist, fd);
	close(fd);
	free(history_path);
}
