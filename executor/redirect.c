/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/05 02:25:10 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	ft_rediter(t_redirection *lst, void (*f)(t_redirection *))
{
	while (lst)
	{
		(*f)(lst);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}

int		has_outward_redirection(t_redirection *lst)
{
	while (lst)
	{
		if (lst->type == REDIRECT_OUT || lst->type == REDIRECT_APPEND)
			return (1);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (0);
}

int		has_inward_redirection(t_redirection *lst)
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

static	char	*read_files_content(char **files)
{
	int		i;
	char	*clear = NULL;
	char	*str = NULL;
	char	*content = ft_strdup("");

	i = 0;
	if (content)
	{
		while (files[i])
		{
			int tmp = open(files[i], O_RDONLY);
			while (tmp >= 0)
			{
				str = get_next_line(tmp);
				if (str)
				{
					clear = content;
					content = ft_strjoin(content, str);
					free(clear);
					free(str);
				}
				else
					break ;
			}
			close(tmp);
			i++;
		}
	}
	return (content);
}

void	detect_out_redirection(t_ast_node *node)
{
	if (has_outward_redirection(node->redirs))
	{
		int tmp = open("__OUTFILE__", O_WRONLY | O_CREAT, 0666);
		if (dup2(tmp, STDOUT_FILENO) == -1)
			perror("(5) Error redirecting");
	}
}

void	detect_in_redirection(t_ast_node *node)
{
	if (has_inward_redirection(node->redirs))
	{
		t_redirection *lst = node->redirs;
		char **arr = malloc(sizeof(char *) * 1);
		arr[0] = NULL;
		while (lst)
		{
			if (lst->type == REDIRECT_IN)
				arr = add_arr_of_strs(arr, lst->file);
			else if (lst->type == REDIRECT_HEREDOC)
			{
				here_doc(lst->file);
				arr = add_arr_of_strs(arr, "__HEREDOC__");
			}
			if (lst->next == NULL)
				break ;
			lst = lst->next;
		}
		char *content = read_files_content(arr);
		if (content)
		{
			int tmp = open("__INFILE__", O_RDWR | O_CREAT | O_TRUNC | O_DSYNC, 0666);
			write(tmp, content, ft_strlen(content));
			close(tmp);
			tmp = open("__INFILE__", O_RDONLY, 0);
			if (dup2(tmp, STDIN_FILENO) == -1)
				perror("(4) Error redirecting");
		}
	}
}

void	pipex_redirect(t_ast_node *node, int fd[2], int files[3], int is_last)
{
	if (files[0] == -1)
	{
		perror("(0) Error reading file");
		exit(0);
	}

	if (has_inward_redirection(node->redirs))
	{
		detect_in_redirection(node);
	}
	else
	{
		if (dup2(files[0], STDIN_FILENO) == -1)
			perror("(1) Error redirecting");
		close(fd[0]);
	}

	if (has_outward_redirection(node->redirs))
	{
		detect_out_redirection(node);
		close(fd[0]);
		close(fd[1]);
	}
	else if (is_last)
	{
		if (dup2(files[1], STDOUT_FILENO) == -1)
			perror("(2) Error redirecting");
		close(fd[0]);
		close(fd[1]);
	}
	else if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("(3) Error redirecting");
		close(fd[0]);
	}
}

static	void	redlist_out(t_redirection *lst, char *content)
{
	int	tmp;
	int	flags;
	while (lst)
	{
		if (lst->type == REDIRECT_OUT || lst->type == REDIRECT_APPEND)
		{
			if (lst->type == REDIRECT_OUT)
				flags = O_WRONLY | O_CREAT | O_TRUNC;
			else
				flags = O_WRONLY | O_CREAT | O_APPEND;
			tmp = open(lst->file, flags, 0666);
			write(tmp, content, ft_strlen(content));
			close(tmp);
		}
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}

void	multiple_output_redirections(t_ast_node *node)
{
	char	**arr;
	char	*content;
	char	*out;

	arr = malloc(sizeof(char *) * 2);
	out = ft_strdup("__OUTFILE__");
	if (arr)
	{
		arr[0] = ft_strdup(out);
		arr[1] = NULL;
		content = read_files_content(arr);
		clear_arr_of_strs(arr);
		if (content)
		{
			redlist_out(node->redirs, content);
			free(content);
		}
	}
	if (access(out, F_OK) == 0)
	{
		unlink(out);
	}
	free(out);
}

void	here_doc(char *delimit)
{
	char	*str;
	int		str_len;
	int		fd;

	fd = open("__HEREDOC__", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	str = get_next_line(STDIN_FILENO);
	str_len = ft_strlen(str);
	while (ft_strncmp(str, delimit, str_len - 1) != 0)
	{
		write(fd, str, ft_strlen(str));
		free(str);
		str = get_next_line(STDIN_FILENO);
		str_len = ft_strlen(str);
	}
	free(str);
	close(fd);
}
