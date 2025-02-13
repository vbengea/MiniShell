/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/13 17:54:12 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

int	detect_out_redirection(t_ast_node *node)
{
	char	*id;
	char	*file;
	int		tmp;
	int		flags;

	if (has_outward_redirection(node))
	{
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
	}
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

int		detect_in_redirection(t_ast_node *node, t_terminal *tty)
{
	if (has_inward_redirection(node->redirs))
	{
		bool			is_first_time;
		t_redirection	*lst = node->redirs;
		char 			**arr;
		char			*file;
		int				tmp;
		char			*content;

		arr = malloc(sizeof(char *) * 2);
		arr[0] = NULL;
		is_first_time = true;
		while (lst)
		{
			if (lst->type == REDIRECT_IN)
			{
				if (is_first_time)
					arr = add_arr_of_strs(arr, lst->file);
				is_first_time = false;
			}
			else if (lst->type == REDIRECT_HEREDOC)
			{
				here_doc(node, lst, 1, tty);
				if (is_first_time)
				{
					file = tmp_path(node->nid, REDIRECT_HEREDOC);
					if (file)
					{
						arr = add_arr_of_strs(arr, file);
						free(file);
					}
				}
				is_first_time = false;
			}
			if (lst->next == NULL)
				break ;
			lst = lst->next;
		}
		content = read_files_content(arr);
		clear_arr_of_strs(arr);
		if (content)
		{
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
			return (1);
		}
	}
	else if (has_group_redirection(node, 1))
	{
		if (node->type != NODE_GROUP && !is_builtin(node))
		{
			if (dup2(node->in_fd, STDIN_FILENO) == -1)
				perror("(7) Error redirecting");
			return (1);
		}
	}
	return (0);
}

char	*read_fd_content(int tmp)
{
	char	*str;
	char	*clear;
	char	*content;

	str = NULL;
	clear = NULL;
	content = ft_strdup("");
	while (tmp >= 0)
	{
		str = get_next_line(tmp);
		if (str)
		{
			clear = content;
			content = ft_strjoin(content, str);
			free(clear);
			free(str);
			if (!content)
				return (NULL);
		}
		else
			break ;
	}
	return (content);
}

char	*read_path_content(char *path)
{
	char	*content;
	char	*clear;
	char	*str;

	content = NULL;
	clear = NULL;
	str = NULL;
	int tmp = open(path, O_RDONLY);
	if(tmp >= 0)
	{
		clear = content;
		str = read_fd_content(tmp);
		if (str)
		{
			if (content)
			{
				content = ft_strjoin(content, str);
				free(clear);
				free(str);
			}
			else
				content = str;
			if (!content)
				return (NULL);
		}
		close(tmp);
	}
	return (content);
}

char	*read_files_content(char **files)
{
	int		i;
	char	*clear;
	char	*str;
	char	*content;

	i = 0;
	str = NULL;
	clear = NULL;
	content = NULL;
	while (files[i])
	{
		int tmp = open(files[i], O_RDONLY);
		if(tmp >= 0)
		{
			clear = content;
			str = read_fd_content(tmp);
			if (str)
			{
				if (content)
				{
					content = ft_strjoin(content, str);
					free(clear);
					free(str);
				}
				else
					content = str;
				if (!content)
					return (NULL);
			}
			close(tmp);
		}
		else
			cleanup(files[i]);
		i++;
	}
	return (content);
}

static	void	redlist_out(t_redirection *lst, char *content)
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
					tmp = interpolation(str, tty);
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