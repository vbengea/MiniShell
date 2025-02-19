/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/19 21:17:30 by jflores          ###   ########.fr       */
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
			return (NULL);
	}
}

char	*read_files_content(char **files)
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
		}
		else
			cleanup(files[i], 1, NULL, NULL);
		i++;
	}
	return (content);
}
