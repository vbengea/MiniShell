/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:53:41 by jflores           #+#    #+#             */
/*   Updated: 2025/03/04 19:07:43 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static	void	write_content(t_ast_node *node, char *content, int tmp, \
	t_terminal *tty)
{
	char	*file;

	file = tmp_path(node->nid, REDIRECT_IN, node, tty);
	if (file)
	{
		tmp = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (tmp >= 0)
		{
			node->in_fd = tmp;
			write(tmp, content, ft_strlen(content));
			close(tmp);
			if (node->type != NODE_GROUP)
			{
				tmp = open(file, O_RDONLY);
				node->in_fd = tmp;
				if (!is_builtin(node))
				{
					if (dup2(node->in_fd, STDIN_FILENO) == -1)
						perror("(4) Error redirecting");
				}
			}
		}
		free(file);
	}
	free(content);
}

static	void	brbin(char ***arr, t_ast_node *node, t_terminal *tty)
{
	char		*file;

	file = tmp_path(node->nid, REDIRECT_IN, node, tty);
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
				brbin(arr, node, tty);
			is_first_time = false;
		}
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
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

void	detect_in_redirection(t_ast_node *node, int hold, t_terminal *tty)
{
	char	**arr;
	char	*content;

	(void) hold;
	if (has_inward_redirection(node->redirs))
	{
		arr = ft_calloc(sizeof(char *), 1);
		brb(node->redirs, &arr, node, tty);
		content = read_files_content(arr, node, tty);
		clear_arr_of_strs(arr);
		if (content)
			write_content(node, content, 0, tty);
	}
	else if (has_group_redirection(node, 1) && node->type != NODE_GROUP && \
	!is_builtin(node))
	{
		if (dup2(node->in_fd, STDIN_FILENO) == -1)
			perror("(7) Error redirecting");
		close(node->in_fd);
	}
}
