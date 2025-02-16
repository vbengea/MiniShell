/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:53:41 by jflores           #+#    #+#             */
/*   Updated: 2025/02/16 11:15:04 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

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

static	void	brb(t_redirection *lst, char ***arr, t_ast_node *node, \
	t_terminal *tty)
{
	bool	is_first_time;

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

int	detect_in_redirection(t_ast_node *node, t_terminal *tty)
{
	char	**arr;
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
	else if (has_group_redirection(node, 1) && node->type != NODE_GROUP && \
	!is_builtin(node))
	{
		if (dup2(node->in_fd, STDIN_FILENO) == -1)
			perror("(7) Error redirecting");
		return (1);
	}
	return (0);
}

void	here_doc(t_ast_node *node, t_redirection *lst, int do_write, \
	t_terminal *tty)
{
	char	*str;
	char	*delimit;
	char	*tmp;
	int		str_len;
	int		fd;

	delimit = lst->file;
	str = tmp_path(node->nid, REDIRECT_HEREDOC);
	if (str)
	{
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		free(str);
		str = get_next_line(STDIN_FILENO);
		str_len = ft_strlen(str);
		while (ft_strncmp(str, delimit, str_len - 1) != 0)
		{
			if (do_write)
			{
				if (lst->is_quote)
				{
					tmp = interpolation(str, -1, tty);
					if (tmp)
					{
						write(fd, tmp, ft_strlen(tmp));
						free(tmp);
					}
				}
				else
					write(fd, str, ft_strlen(str));
			}
			free(str);
			str = get_next_line(STDIN_FILENO);
			str_len = ft_strlen(str);
		}
		free(str);
		close(fd);
	}
}

void	pipex_redirect_in(t_ast_node *node, int fd[2], int is_last, \
	t_terminal *tty)
{
	(void) is_last;
	(void) fd;
	if (!detect_in_redirection(node, tty) && tty->files[0] != STDIN_FILENO && \
	dup2(tty->files[0], STDIN_FILENO) == -1)
		perror("(1) Error redirecting");
}

int	has_inward_redirection(t_redirection *lst)
{
	while (lst)
	{
		if (lst->type == REDIRECT_IN || lst->type == REDIRECT_HEREDOC)
			return (1);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (0);
}
