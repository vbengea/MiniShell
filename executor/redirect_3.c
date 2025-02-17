/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/16 19:40:37 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*tmp_path(int nid, t_redirect_type type)
{
	char	*id;
	char	*file;

	id = ft_itoa(nid);
	file = NULL;
	if (id)
	{
		if (type == REDIRECT_OUT || type == REDIRECT_APPEND)
			file = ft_strjoin("tmp/__OUTFILE__", id);
		else if (type == REDIRECT_IN)
			file = ft_strjoin("tmp/__INFILE__", id);
		else if (type == REDIRECT_HEREDOC)
			file = ft_strjoin("tmp/__HEREDOC__", id);
		free(id);
	}
	return (file);
}

static	void	heredoc_inner(char *str, int fd, t_redirection *lst, \
	t_terminal *tty)
{
	char	*tmp;

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

void	here_doc(t_ast_node *node, t_redirection *lst, int do_write, \
	t_terminal *tty)
{
	char	*str;
	char	*delimit;
	int		str_len;
	int		fd;

	delimit = lst->file;
	str = tmp_path(node->nid, REDIRECT_IN);
	if (str)
	{
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
			cleanup("Error reading file", 1);
		free(str);
		str = get_next_line(STDIN_FILENO);
		str_len = ft_strlen(str);
		while (ft_strncmp(str, delimit, str_len - 1) != 0)
		{
			if (do_write)
				heredoc_inner(str, fd, lst, tty);
			free(str);
			str = get_next_line(STDIN_FILENO);
			str_len = ft_strlen(str);
		}
		free(str);
		close(fd);
	}
}
