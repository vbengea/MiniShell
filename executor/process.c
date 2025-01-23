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

void	redirect(int fd[2], struct s_node **children, node_type type)
{
	int	inre;
	int	outre;

	if (children[0]->stdin)
	{
		inre = -1;
		if (children[0]->stdin == INFILE)
			inre = open(children[0]->stdin_value, O_RDONLY);
		else if (children[0]->stdin == HEREDOC)
			inre = here_doc(children[0]->stdin_value);
		if (inre < 0 || dup2(inre, STDIN_FILENO) == -1)
			cleanup("Error redirecting");
	}
	if (children[0]->stdout)
	{
		outre = -1;
		if (children[0]->stdout == OUTFILE)
			outre = open(children[0]->stdout_value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (children[0]->stdout == APPEND)
			outre = open(children[0]->stdout_value, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (outre < 0 || dup2(outre, STDOUT_FILENO) == -1)
			cleanup("Error redirecting");
	}
	else if (type == PIPE && *(children + 1) && (dup2(fd[1], STDOUT_FILENO) == -1))
		cleanup("Error redirecting");
}

void	parent(int fd[2], struct s_node **children, char **env, node_type type)
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
	if (dup2(fd[0], STDIN_FILENO) == -1)
		cleanup("Error changing STD IN");
	if (*(children + 1))
	{
		close(fd[1]);
		pipex(++children, env, NULL, type);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
}

void	child(int fd[2], struct s_node **children, char **env, node_type type)
{
	redirect(fd, children, type);
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
			process(children[0], env, fd);
		}
	}
}

void	pipex(struct s_node **children, char **env, int files[2], node_type type)
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

void	process(t_node *node, char **env, int fd[2])
{
	pipex(node->children, env, fd, node->type);
}
