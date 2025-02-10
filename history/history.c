/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:08 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/10 19:34:21 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*get_history_filepath(char **env)
{
	char	*home;

	home = get_env("HOME", env);
	if (!home)
		return (NULL);
	return (ft_strjoin(home, HISTORY_FILE));
}

void	load_history_from_file(char **env)
{
	char	*history_path;

	history_path = get_history_filepath(env);
	if (history_path)
	{
		read_history(history_path);
		free (history_path);
	}
}

void	save_history_to_file(char **env)
{
	char	*history_path;

	history_path = get_history_filepath(env);
	if (history_path)
	{
		write_history(history_path);
		free (history_path);
	}
}
