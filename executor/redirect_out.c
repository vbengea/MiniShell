/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:53:37 by jflores           #+#    #+#             */
/*   Updated: 2025/02/20 23:40:56 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

int	do_outward_redirection(t_ast_node *node, t_terminal *tty)
{
	char	*id;
	char	*file;
	int		tmp;
	int		flags;

	id = ft_itoa(node->nid);
	file = tmp_path(node->nid, REDIRECT_OUT);
	flags = O_WRONLY | O_CREAT | O_TRUNC | O_APPEND;
	tmp = open(file, flags, 0666);
	if (tmp < 0)
		cleanup("Error reading file", 1, node, tty);
	free(id);
	free(file);
	if (tmp < 0)
		return (0);
	node->out_fd = tmp;
	if (node->type != NODE_GROUP && !is_builtin(node))
	{
		if (dup2(tmp, STDOUT_FILENO) == -1)
			perror("(5) Error redirecting");
		close(tmp);
		return (1);
	}
	return (0);
}

int	detect_out_redirection(t_ast_node *node, t_terminal *tty)
{
	if (has_outward_redirection(node, tty))
		return (do_outward_redirection(node, tty));
	else if (has_group_redirection(node, 0))
	{
		if (node->type != NODE_GROUP && !is_builtin(node))
		{
			if (dup2(node->out_fd, STDOUT_FILENO) == -1)
				perror("(6) Error redirecting");
			close(node->out_fd);
			return (1);
		}
	}
	return (0);
}

int	has_outward_redirection(t_ast_node *ast, t_terminal *tty)
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
			if (fd < 0)
				cleanup("Error reading file", 1, ast, tty);
			close(fd);
		}
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (has_redirect);
}

void	redlist_out(t_redirection *lst, char *content, t_ast_node *node, \
	t_terminal *tty)
{
	int				tmp;
	int				flags;
	t_redirection	*last;

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
		if (tmp < 0)
			cleanup("Error reading file", 1, node, tty);
		write(tmp, content, ft_strlen(content));
		close(tmp);
	}
}

void	multiple_output_redirections(t_ast_node *node, t_terminal *tty)
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
				redlist_out(node->redirs, content, node, tty);
				free(content);
			}
			if (access(file, F_OK) == 0)
				unlink(file);
			free(file);
		}
	}
}
