/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/14 21:58:58 by jflores          ###   ########.fr       */
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

static	void	write_content(t_ast_node *node, char *content)
{
	int		tmp;
	char	*file;

	file = tmp_path(node->nid, REDIRECT_IN);
	if (file)
	{
		tmp = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (tmp >= 0)
		{
			write(tmp, content, ft_strlen(content));
			node->in_fd = tmp;
			close(tmp);
			if (node->type != NODE_GROUP && !is_builtin(node))
			{
				tmp = open(file, O_RDONLY);
				node->in_fd = tmp;
				if (dup2(node->in_fd, STDIN_FILENO) == -1)
					perror("(4) Error redirecting");
			}
		}
		free(file);
	}
	free(content);
}

static	void	brbin(char ***arr, t_ast_node *node)
{
	char		*file;

	file = tmp_path(node->nid, REDIRECT_HEREDOC);
	if (file)
	{
		*arr = add_arr_of_strs(*arr, file);
		free(file);
	}
}

static	void	brb(t_redirection *lst, char ***arr, t_ast_node *node, t_terminal *tty)
{
	bool		is_first_time;

	is_first_time = true;
	while (lst)
	{
		if (lst->type == REDIRECT_IN)
		{
			if (is_first_time)
				*arr = add_arr_of_strs(*arr, lst->file);
			is_first_time = false;
		}
		else if (lst->type == REDIRECT_HEREDOC)
		{
			here_doc(node, lst, 1, tty);
			if (is_first_time)
				brbin(arr, node);
			is_first_time = false;
		}
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}

int		detect_in_redirection(t_ast_node *node, t_terminal *tty)
{
	char 	**arr;
	char	*content;

	if (has_inward_redirection(node->redirs))
	{
		arr = ft_calloc(sizeof(char *), 1);
		brb(node->redirs, &arr, node, tty);
		content = read_files_content(arr);
		clear_arr_of_strs(arr);
		if (content)
		{
			write_content(node, content);
			return (1);
		}
	}
	else if (has_group_redirection(node, 1) && node->type != NODE_GROUP && !is_builtin(node))
	{
		if (dup2(node->in_fd, STDIN_FILENO) == -1)
			perror("(7) Error redirecting");
		return (1);
	}
	return (0);
}
