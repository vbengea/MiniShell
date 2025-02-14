/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/14 22:01:59 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

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

void	redlist_out(t_redirection *lst, char *content)
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
