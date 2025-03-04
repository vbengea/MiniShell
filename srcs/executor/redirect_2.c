/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/03/04 19:07:32 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

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
	int		tmp;

	content = NULL;
	tmp = open(path, O_RDONLY);
	if (tmp >= 0)
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
		}
		close(tmp);
	}
	return (content);
}

void	read_files_inner(int tmp, char **content)
{
	char	*clear;
	char	*str;

	clear = *content;
	str = read_fd_content(tmp);
	if (str)
	{
		if (*content)
		{
			*content = ft_strjoin(*content, str);
			free(clear);
			free(str);
		}
		else
			*content = str;
		if (!*content)
			return ;
	}
}

char	*read_files_content(char **files, t_ast_node *node, t_terminal *tty)
{
	int		i;
	int		tmp;
	char	*content;

	i = 0;
	content = NULL;
	while (files[i])
	{
		tmp = open(files[i], O_RDONLY);
		if (tmp >= 0)
		{
			read_files_inner(tmp, &content);
			close(tmp);
			if (!content)
				return (NULL);
		}
		else
			cleanup(files[i], 1, node, tty);
		i++;
	}
	return (content);
}
