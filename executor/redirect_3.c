/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/20 23:10:05 by jflores          ###   ########.fr       */
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
		else if (type == REDIRECT_IN || type == REDIRECT_HEREDOC)
			file = ft_strjoin("tmp/__INFILE__", id);
		free(id);
	}
	return (file);
}

static	void	heredoc_inner(char *str, int fd, t_redirection *lst, \
	t_terminal *tty)
{
	char	*tmp;
	char	*s;

	s = str;
	if (lst->is_quote)
	{
		tmp = interpolation(s, -1, tty);
		if (tmp)
		{
			write(fd, tmp, ft_strlen(tmp));
			free(tmp);
		}
	}
	else
		write(fd, s, ft_strlen(s));
}

void	here_doc(t_ast_node *node, t_redirection *lst, int do_write, \
	t_terminal *tty)
{
	char	*str;
	int		fd;
	char	*delimit;

	delimit = ft_strjoin(lst->file, "\n");
	if (delimit)
	{
		str = tmp_path(node->nid, REDIRECT_IN);
		if (str)
		{
			fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			free(str);
			if (fd < 0)
				cleanup("Error reading file", 1, node, tty);
			while (1)
			{
				write(1, "> ", 2);
				str = get_next_line(tty->files[0]);
				if (str)
				{
					if (ft_cmpexact(str, delimit))
					{
						free(str);
						break ;
					}
					if (do_write)
						heredoc_inner(str, fd, lst, tty);
					free(str);
				}
				else
					break ;
			}
			close(fd);
		}
		free(delimit);
	}
}
