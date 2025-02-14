/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/14 19:51:22 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

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

void	here_doc(t_ast_node *node, t_redirection *lst, int do_write, t_terminal *tty)
{
	char	*str;
	char	*file;
	int		str_len;
	int		fd;
	char	*delimit;
	char	*tmp;

	delimit = lst->file;
	file = tmp_path(node->nid, REDIRECT_HEREDOC);
	if (file)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		free(file);
		str = get_next_line(STDIN_FILENO);
		str_len = ft_strlen(str);
		while (ft_strncmp(str, delimit, str_len - 1) != 0)
		{
			if (do_write)
			{
				if (lst->is_quote)
				{
					tmp = interpolation(str, -1, tty);
					if  (tmp)
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

void	pipex_redirect_in(t_ast_node *node, int fd[2], int is_last, t_terminal *tty)
{
	(void) is_last;
	(void) fd;
	if (!detect_in_redirection(node, tty) && tty->files[0] != STDIN_FILENO && dup2(tty->files[0], STDIN_FILENO) == -1)
		perror("(1) Error redirecting");
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
