/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:22:19 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/25 17:02:39 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static	void	waitit(t_node_type_u type)
{
	int		status;

	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			if (access("__tmp__", F_OK) == 0)
				unlink("__tmp__");
			if (status != 0 && type == AND)
				exit(0);
			else if (status == 0 && type == OR)
				exit(0);
			break ;
		}
	}
}

void	parent(int fd[2], struct s_node **children, char **env, \
	t_node_type_u type)
{
	waitit(type);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		cleanup("Error changing STD IN");
	if (*(children + 1))
	{
		close(fd[1]);
		process(++children, env, NULL, type);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
}

void	child(int fd[2], struct s_node **children, char **env, \
	t_node_type_u type)
{
	redirect_stdin(children);
	redirect_stdout(fd, children, type);
	if (children)
	{
		if (children[0]->type == EXEC)
		{
			if (execute(children[0]->value, env) == -1)
				cleanup("Error executing command");
		}
		else
		{
			close(fd[0]);
			process(children[0]->children, env, fd, children[0]->type);
		}
	}
}

void	process(struct s_node **children, char **env, int files[2], \
	t_node_type_u type)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		cleanup("Error creating pipe");
	pid = fork();
	if (pid == -1)
		cleanup("Error forking process");
	if (pid == 0)
	{
		if (files && *(children + 1) == NULL)
			fd[1] = files[1];
		child(fd, children, env, type);
	}
	else
	{
		parent(fd, children, env, type);
	}
}
