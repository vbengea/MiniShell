/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/25 16:31:33 by juaflore         ###   ########.fr       */
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
			while (1)
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

void	detect_file_redirection(t_ast_node *node)
{
	if (has_outward_redirection(node->redirs))
	{
		int tmp = open("__tmp__", O_WRONLY | O_CREAT, 0666);
		if (dup2(tmp, STDOUT_FILENO) == -1)
			perror("Error redirecting");
	}
	else if (node->redirs)
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
			int tmp = open("__tmp__", O_RDWR | O_CREAT | O_TRUNC | O_DSYNC, 0666);
			write(tmp, content, ft_strlen(content));
			close(tmp);
			tmp = open("__tmp__", O_RDONLY, 0);
			if (dup2(tmp, STDIN_FILENO) == -1)
				perror("Error INFILE redirecting");
		}
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
	char **arr = malloc(sizeof(char *) * 2);
	arr[0] = "__tmp__";
	arr[1] = NULL;
	char *content = read_files_content(arr);
	if (content)
	{
		redlist_out(node->redirs, content);
		free(content);
	}
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

void	pipex_redirect(t_ast_node *node, int fd[2], int files[3], int is_last)
{
	(void) node;
	if (files[0] == -1)
	{
		perror("Error reading file");
		exit(1);
	}
	if (node->redirs)
	{
		int tmp = open("__tmp__", O_WRONLY | O_CREAT, 0666);
		if (dup2(tmp, STDOUT_FILENO) == -1)
			perror("Error redirecting");
	}
	else if (is_last)
	{
		if (dup2(files[1], STDOUT_FILENO) == -1)
			perror("Error redirecting");
	}
	else if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("Error redirectingT");
	if (dup2(files[0], STDIN_FILENO) == -1)
		perror("Error redirecting");
	close(fd[0]);
	close(fd[1]);
}

void	redirecter(t_ast_node *node, char ***env, int hold, int files[3])
{
	(void) hold;
	int	f = 0;
	if (node->redirect_type == REDIRECT_OUT)
	{
		f = open(node->file, O_RDONLY | O_CREAT | O_TRUNC, 0777);
		if (dup2(f, STDOUT_FILENO) == -1)
			perror("Error redirecting");
	}
	else if (node->redirect_type == REDIRECT_IN)
	{
		f = open(node->file, O_RDONLY);
		if (dup2(f, STDIN_FILENO) == -1)
			perror("Error redirecting");
	}
	else if (node->redirect_type == REDIRECT_APPEND)
	{
		f = open(node->file, O_RDONLY | O_CREAT | O_APPEND, 0666);
		if (dup2(f, STDOUT_FILENO) == -1)
			perror("Error redirecting");
	}
	else if (node->redirect_type == REDIRECT_HEREDOC)
	{
		// f = here_doc(node->file, STDIN_FILENO);
		// if (dup2(f, STDIN_FILENO) == -1)
		// 	perror("Error redirecting");
	}
	if (!node->parent || node->parent->type != NODE_PIPE)
		navigator(node, env, 1, files);
}
