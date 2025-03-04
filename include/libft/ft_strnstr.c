/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:17:59 by juaflore          #+#    #+#             */
/*   Updated: 2024/09/21 19:10:08 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char				*p;
	unsigned int		j;
	size_t				sz;
	size_t				biglen;

	biglen = ft_strlen(big);
	sz = ft_strlen(little);
	p = (char *)big;
	if (sz == 0)
		return (p);
	j = 0;
	while (j < len && j < biglen)
	{
		if (ft_strncmp((p + j), little, sz) == 0 && j + sz <= len)
			return ((p + j));
		j++;
	}
	return (NULL);
}
