/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/24 13:43:20 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	bedirect(int fd[2], struct s_node **bhildren, node_type type)
{
	int	inre;
	int	outre;

	if (type == PIPE && *(bhildren + 1) && (dup2(fd[1], \
		STDOUT_FILENO) == -1))
		cleanup("Error redirecting");
}

static	void	baitit(node_type type)
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

void	barent(int fd[2], t_ast_node *node, char **env)
{
	baitit(node->type);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		cleanup("Error changing STD IN");
	if (*(node + 1))
	{
		close(fd[1]);
		bipex(++node, env, NULL);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
}

void	bhild(int fd[2], t_ast_node *node, char **env)
{
	bedirect(fd, node, node->type);
	if (node)
	{
		if (node->type == EXEC)
		{
			if (execute(node->args, env) == -1)
				cleanup("Error executing command");
		}
		else
		{
			close(fd[0]);
			binary(node, env, fd);
		}
	}
}

void	bipex(t_ast_node *node, char **env, int files[2])
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
		bhild(fd, node->left, env);
	}
	else
	{
		barent(fd, node, env);
	}
}

void	binary(t_ast_node *s, char **env, int fd[2])
{
	if (s->type == NODE_PIPE)
		bipex(s, env, fd);
}