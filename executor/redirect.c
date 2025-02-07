/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/07 04:07:43 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	t_redirection	*parent_lookup(t_ast_node *ast)
{
	while (ast)
	{
		if (ast->parent == NULL)
			break ;
		ast = ast->parent;
		if (ast->type == NODE_GROUP && ast->redirs)
			return (ast->redirs);
	}
	return (NULL);
}

void	detect_out_redirection(t_ast_node *node)
{
	(void) parent_lookup;
	if (has_outward_redirection(node))
	{
		char	*id = ft_itoa(node->nid);
		char	*file = ft_strjoin("__OUTFILE__", id);
		int 	tmp = open(file, O_WRONLY | O_CREAT, 0666);
		free(id);
		free(file);
		if (tmp < 0)
			return ;
		node->fd = tmp;
		if (!is_builtin(node))
		{
			if (dup2(tmp, STDOUT_FILENO) == -1)
				perror("(5) Error redirecting");
		}
	}
}

t_redirection	*ft_lstred(t_redirection *node)
{
	t_redirection	*lst;

	lst = malloc(sizeof(t_redirection));
	if (lst)
	{
		lst->file = node->file;
		lst->type = node->type;
		lst->otype = node->otype;
		lst->next = NULL;
	}
	return (lst);
}

void	executer(t_redirection *lst, t_redirection **rev)
{
	redlist_add(rev, ft_lstred(lst));
	if(lst->next)
		executer(lst->next, rev);
}

void	detect_in_redirection(t_ast_node *node)
{
	if (has_inward_redirection(node->redirs))
	{
		bool	is_first_time;
		t_redirection *lst = node->redirs;
		t_redirection *rev = NULL;
		char **arr = malloc(sizeof(char *) * 2);
		arr[0] = NULL;
		is_first_time = true;
		executer(lst, &rev);
		lst = rev;
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
				here_doc(lst->file, 1);
				if (is_first_time)
					arr = add_arr_of_strs(arr, "__HEREDOC__");
				is_first_time = false;
			}
			if (lst->next == NULL)
				break ;
			lst = lst->next;
		}
		char *content = read_files_content(arr);
		if (content)
		{
			int tmp = open("__INFILE__", O_RDWR | O_CREAT | O_TRUNC, 0666);
			write(tmp, content, ft_strlen(content));
			close(tmp);
			tmp = open("__INFILE__", O_RDONLY, 0);

			if (is_builtin(node))
				node->fd = tmp;
			else
			{
				if (dup2(tmp, STDIN_FILENO) == -1)
					perror("(4) Error redirecting");
			}
		}
	}
}

int		has_outward_redirection(t_ast_node *ast)
{
	t_redirection	*lst;

	lst = ast->redirs;
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

char	*read_files_content(char **files)
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

	if (has_outward_redirection(node))
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
	int	is_first;

	is_first = 1;
	while (lst)
	{
		if (lst->type == REDIRECT_OUT || lst->type == REDIRECT_APPEND)
		{
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
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}

void	multiple_output_redirections(t_ast_node *node)
{
	char	**arr;
	char	*content;

	if (has_outward_redirection(node))
	{
		arr = malloc(sizeof(char *) * 2);
		char	*id = ft_itoa(node->nid);
		char	*out = ft_strjoin("__OUTFILE__", id);
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
		free(id);
	}
}

void	here_doc(char *delimit, int do_write)
{
	char	*str;
	int		str_len;
	int		fd;

	fd = open("__HEREDOC__", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	str = get_next_line(STDIN_FILENO);
	str_len = ft_strlen(str);
	while (ft_strncmp(str, delimit, str_len - 1) != 0)
	{
		if (do_write)
			write(fd, str, ft_strlen(str));
		free(str);
		str = get_next_line(STDIN_FILENO);
		str_len = ft_strlen(str);
	}
	free(str);
	close(fd);
}
