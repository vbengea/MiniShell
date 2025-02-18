/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/18 18:47:31 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*environment(char *name, t_terminal *tty)
{
	int		i;
	int		j;
	int		n;
	char	*str;

	i = 0;
	n = ft_strlen(name);
	while (tty->env[i])
	{
		j = 0;
		while (tty->env[i][j] && tty->env[i][j] != '=')
			j++;
		str = ft_substr(tty->env[i], 0, j);
		if (ft_strncmp(str, name, n) == 0)
		{
			free(str);
			return (tty->env[i] + j + 1);
		}
		free(str);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char *penv)
{
	int		i;
	char	**pathenv;
	char	*command;
	char	*segments;

	pathenv = ft_split(penv, ':');
	i = 0;
	while (pathenv && cmd && pathenv[i])
	{
		segments = ft_strjoin(pathenv[i++], "/");
		command = ft_strjoin(segments, cmd);
		free(segments);
		if (access(command, F_OK | X_OK) == 0)
		{
			clear_arr_of_strs(pathenv);
			return (command);
		}
		free(command);
	}
	clear_arr_of_strs(pathenv);
	return (NULL);
}

int	doexec(char *path, t_ast_node *node, char **comm, int is_free, t_terminal *tty)
{
	char	**p;

	if ((path && access(path, X_OK) == 0))
	{
		p = env_resolution(tty);
		if (p && execve(path, (comm + node->args_index), p) == -1)
		{
			if (is_free)
				free(path);
			clear_arr_of_strs(comm);
			cleanup("Error executing command", 126);
			return (-1);
		}
	}
	if (path && is_free)
		free(path);
	clear_arr_of_strs(comm);
	cleanup("Error executing command", 127);
	return (-1);
}

char	*get_command_path(char *cmd, int *i, int *is_free, t_terminal *tty)
{
	char	*path;
	char	*penv;

	if (ft_strchr(cmd, '/') != NULL || \
		ft_strchr(cmd, '.') != NULL || \
		ft_cmpexact(cmd, "minishell"))
	{
		path = ft_strdup(cmd);
		if (ft_strncmp(path, "./", 2) == 0)
			*i = 2;
	}
	else
	{
		penv = environment("PATH", tty);
		if (penv)
		{
			path = find_path(cmd, penv);
			*is_free = 1;
		}
		else
			path = NULL;
	}
	return (path);
}

int	execute(t_ast_node *node, char **comm, t_terminal *tty)
{
	char	*path;
	int		is_free;
	int		i;

	is_free = 0;
	i = 0;
	if (comm)
	{
		path = get_command_path(comm[node->args_index], &i, &is_free, tty);
		return (doexec(path + i, node, comm, is_free, tty));
	}
	return (0);
}
