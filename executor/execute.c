/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/25 16:37:00 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

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
	cleanup("Error executing command");
	return (-1);
}

int	bexecute(char **comm, char **arvp)
{
	char	*path;
	char	*env;
	int		is_free;

	is_free = 0;
	if (comm)
	{
		if (ft_strchr(comm[0], '/') != NULL)
			path = comm[0];
		else
		{
			env = environment("PATH", arvp);
			if (env)
			{
				path = find_path(comm[0], env);
				is_free = 1;
			}
			else
				path = NULL;
		}
		return (doexec(path, comm, arvp, is_free));
	}
	return (0);
}

int	execute(char *cmd, char **arvp)
{
	char	**comm;
	char	*path;
	char	*env;
	int		is_free;

	comm = ft_split(cmd, ' ');
	is_free = 0;
	if (comm)
	{
		if (ft_strchr(comm[0], '/') != NULL)
			path = comm[0];
		else
		{
			env = environment("PATH", arvp);
			if (env)
			{
				path = find_path(cmd, env);
				is_free = 1;
			}
			else
				path = NULL;
		}
		return (doexec(path, comm, arvp, is_free));
	}
	return (0);
}
