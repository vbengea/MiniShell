/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:07:37 by juandanielf       #+#    #+#             */
/*   Updated: 2024/10/30 10:03:09 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_buffer(char *str, char **buffer, size_t index)
{
	size_t	j;
	size_t	i;

	i = 0;
	while (str[index + i])
		i++;
	(*buffer) = malloc(i + 1);
	if (*buffer)
	{
		j = 0;
		while (str[index])
			(*buffer)[j++] = str[index++];
		(*buffer)[i] = '\0';
	}
}

size_t	size_str(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	*cap_alloc(char *str, size_t index, char **buffer)
{
	char	*s;
	size_t	i;
	size_t	len;

	len = size_str(str);
	s = NULL;
	if (str)
	{
		s = malloc(index + 1);
		if (s)
		{
			i = 0;
			while (str[i] && i < index)
			{
				s[i] = str[i];
				i++;
			}
			s[index] = '\0';
			if (len > index)
				fill_buffer(str, buffer, index);
		}
		free(str);
	}
	return (s);
}
