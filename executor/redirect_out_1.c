/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:53:37 by jflores           #+#    #+#             */
/*   Updated: 2025/02/16 02:05:56 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	int	do_outward_redirection(t_ast_node *node)
{
	char	*id;
	char	*file;
	int		tmp;
	int		flags;

	id = ft_itoa(node->nid);
	file = tmp_path(node->nid, REDIRECT_OUT);
	flags = O_WRONLY | O_CREAT | O_TRUNC | O_APPEND;
	tmp = open(file, flags, 0666);
	free(id);
	free(file);
	if (tmp < 0)
		return (0);
	node->out_fd = tmp;
	if (node->type != NODE_GROUP && !is_builtin(node))
	{
		if (dup2(tmp, STDOUT_FILENO) == -1)
			perror("(5) Error redirecting");
		return (1);
	}
	return (0);
}

int	detect_out_redirection(t_ast_node *node)
{
	if (has_outward_redirection(node))
		return (do_outward_redirection(node));
	else if (has_group_redirection(node, 0))
	{
		if (node->type != NODE_GROUP && !is_builtin(node))
		{
			if (dup2(node->out_fd, STDOUT_FILENO) == -1)
					perror("(6) Error redirecting");
			return (1);
		}
	}
	return (0);
}

int		has_outward_redirection(t_ast_node *ast)
{
	t_redirection	*lst;
	int				has_redirect;
	int				flags;
	int				fd;

	has_redirect = 0;
	lst = ast->redirs;
	while (lst)
	{
		if (lst->type == REDIRECT_OUT || lst->type == REDIRECT_APPEND)
		{
			has_redirect = 1;
			flags = O_WRONLY | O_CREAT | O_TRUNC;
			if (lst->type == REDIRECT_APPEND)
				flags = O_WRONLY | O_CREAT | O_APPEND;
			fd = open(lst->file, flags, 0666);
			if (fd >= 0)
				close(fd);
		}
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (has_redirect);
}

void	redlist_out(t_redirection *lst, char *content)
{
	int				tmp;
	int				flags;
	int				is_first;
	t_redirection	*last;

	is_first = 1;
	while (lst)
	{
		if (lst->type == REDIRECT_OUT || lst->type == REDIRECT_APPEND)
			last = lst;
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	if (last)
	{
		lst = last;
		if (lst->type == REDIRECT_OUT)
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		else
			flags = O_WRONLY | O_CREAT | O_APPEND;
		tmp = open(lst->file, flags, 0666);
		if (is_first)
		{
			write(tmp, content, ft_strlen(content));
			is_first = 0;
		}
		close(tmp);
	}
}

void	multiple_output_redirections(t_ast_node *node)
{
	char	*content;
	char	*file;

	if (node->has_group_out_fd == 0)
	{
		file = tmp_path(node->nid, REDIRECT_OUT);
		if (file)
		{
			content = read_path_content(file);
			if (content)
			{
				redlist_out(node->redirs, content);
				free(content);
			}
			if (access(file, F_OK) == 0)
				unlink(file);
			free(file);
		}
	}
}

void	pipex_redirect_out(t_ast_node *node, int fd[2], int is_last, t_terminal *tty)
{
	(void) tty;
	if (detect_out_redirection(node))
		close(fd[1]);
	else if (is_last)
		close(fd[1]);
	else if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("(3) Error redirecting");
}
