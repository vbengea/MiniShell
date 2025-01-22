/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:26:48 by juaflore          #+#    #+#             */
/*   Updated: 2024/09/28 14:47:38 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	bytes;
	void	*mem;

	bytes = nmemb * size;
	if (size > bytes && nmemb > bytes)
		return (NULL);
	mem = malloc(bytes);
	if (mem)
		ft_bzero(mem, bytes);
	return (mem);
}

void	clear_arr_of_strs(char **sp)
{
	char	**p;
	char	*str;

	p = sp;
	if (sp != NULL)
	{
		while (*p)
		{
			str = *p;
			free(str);
			p++;
		}
		free(sp);
	}
}
