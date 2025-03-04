/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:07:41 by juandanielf       #+#    #+#             */
/*   Updated: 2024/10/30 10:03:06 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	newline_index(char *str, int bytes, size_t len)
{
	int	i;
	int	index;

	i = 0;
	index = -1;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\n')
			{
				index = i + 1;
				break ;
			}
			i++;
		}
		if ((bytes == 0 && !str[0]) || bytes < 0)
		{
			free(str);
			return (-2);
		}
		else if (bytes < (int)BUFFER_SIZE && index == -1)
			index = len + bytes;
	}
	return (index);
}

static	void	*reallocation(char *str, size_t size, size_t slen)
{
	char	*s;
	size_t	i;
	size_t	j;

	j = slen + size * BUFFER_SIZE;
	s = malloc(j + 1);
	if (s)
	{
		i = 0;
		while (str && str[i])
		{
			s[i] = str[i];
			i++;
		}
		while (i <= j)
			s[i++] = '\0';
	}
	if (str)
		free(str);
	return (s);
}

static	char	*fetch_line(char **buffer, int fd, char *str)
{
	int				index;
	int				i;
	int				bytes;
	size_t			len;

	i = 1;
	index = newline_index(str, BUFFER_SIZE, 0);
	while (index == -1)
	{
		len = size_str(str);
		str = reallocation(str, i++, len);
		if (!str)
			return (NULL);
		bytes = read(fd, (str + len), BUFFER_SIZE);
		if (bytes == -1 || (bytes == 0 && !str[0]))
		{
			free(str);
			return (NULL);
		}
		str[len + bytes] = '\0';
		index = newline_index(str, bytes, len);
		if (index == -2)
			return (NULL);
	}
	return (cap_alloc(str, index, buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*str;

	str = NULL;
	if (fd != -1)
	{
		if (buffer)
			str = buffer;
		buffer = NULL;
		str = fetch_line(&buffer, fd, str);
	}
	return (str);
}
