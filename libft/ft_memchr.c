/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:26:33 by juaflore          #+#    #+#             */
/*   Updated: 2024/09/24 11:25:17 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	signed char		*p;
	signed char		ch;

	i = 0;
	p = (signed char *)s;
	ch = c;
	while (i < n)
	{
		if (p[i] == ch)
			return (p + i);
		i++;
	}
	return (NULL);
}
