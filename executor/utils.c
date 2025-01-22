/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/22 12:39:21 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

char	*environment(char *name, char **env)
{
	int		i;
	int		j;
	int		n;
	char	*str;

	i = 0;
	n = ft_strlen(name);
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		str = ft_substr(env[i], 0, j);
		if (ft_strncmp(str, name, n) == 0)
		{
			free(str);
			return (env[i] + j + 1);
		}
		free(str);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char *env)
{
	int		i;
	char	**pathenv;
	char	**tokens;
	char	*command;
	char	*segments;

	pathenv = ft_split(env, ':');
	tokens = ft_split(cmd, ' ');
	i = 0;
	while (pathenv && tokens && pathenv[i])
	{
		segments = ft_strjoin(pathenv[i++], "/");
		command = ft_strjoin(segments, tokens[0]);
		free(segments);
		if (access(command, F_OK | X_OK) == 0)
		{
			clear_arr_of_strs(pathenv);
			clear_arr_of_strs(tokens);
			return (command);
		}
		free(command);
	}
	clear_arr_of_strs(pathenv);
	clear_arr_of_strs(tokens);
	return (NULL);
}

void	cleanup(char *err, char **commands)
{
	if (commands)
		clear_arr_of_strs(commands);
	perror(err);
	exit(1);
}

int	has_blank(char *str)
{
	if (ft_strchr(str, ' ') || ft_strchr(str, '\t' || ft_strchr(str, '\n') || \
		ft_strchr(str, '\v' || ft_strchr(str, '\r') || ft_strchr(str, '\f'))))
	{
		return (1);
	}
	return (0);
}

int	doexec(char *path, char **comm, char **arvp, int is_free)
{
	if (path && access(path, F_OK | X_OK) == 0)
	{
		if (execve(path, comm, arvp) == -1)
		{
			if (is_free)
				free(path);
			clear_arr_of_strs(comm);
		}
	}
	if (path && is_free)
		free(path);
	clear_arr_of_strs(comm);
	cleanup("Error executing command", NULL);
	return (-1);
}
