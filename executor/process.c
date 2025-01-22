/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:22:19 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/22 12:36:14 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

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

void	parent(int files[2], char **arvp, char **commands, int fd[2])
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		cleanup("Error changing STD IN", commands);
	if (*(commands + 1))
	{
		files[0] = fd[0];
		close(fd[1]);
		pipex(files, arvp, ++commands);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		close(files[1]);
		if (access("__tmp__", F_OK) == 0)
			unlink("__tmp__");
	}
}

void	children(int fd[2], int files[2], char **commands, char **arvp)
{
	if (files[0] == -1 || dup2(files[0], STDIN_FILENO) == -1)
		cleanup("Error reading file", commands);
	if (*(commands + 1) == NULL)
	{
		if (dup2(files[1], STDOUT_FILENO) == -1)
			cleanup("Error changing STD OUT", commands);
	}
	else if (dup2(fd[1], STDOUT_FILENO) == -1)
		cleanup("Error changing STD OUT", commands);
	close(fd[0]);
	close(files[0]);
	if (execute(commands[0], arvp) == -1)
		cleanup("Error executing command", commands);
}

void	pipex(int files[2], char **arvp, char **commands)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		cleanup("Error creating pipe", commands);
	pid = fork();
	if (pid == -1)
		cleanup("Error forking process", commands);
	if (pid == 0)
		children(fd, files, commands, arvp);
	else
		parent(files, arvp, commands, fd);
}

void	process(int argc, char **argv, char **arvp, int files[2])
{
	char	**commands;
	int		status;
	int		i;
	int		j;
	int		k;

	i = argument_index(argv);
	j = 0;
	k = argc - (i + 1);
	commands = malloc(sizeof(char *) * (k + 1));
	while (i < argc - 1)
		commands[j++] = ft_strdup(argv[i++]);
	commands[k] = NULL;
	pipex(files, arvp, commands);
	clear_arr_of_strs(commands);
	while (1)
		if (waitpid(-1, &status, 0) == -1)
			break ;
}
