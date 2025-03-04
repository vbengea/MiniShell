/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:34:04 by juandanielf       #+#    #+#             */
/*   Updated: 2024/09/21 18:01:15 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (*dst && i < size)
	{
		i++;
		dst++;
	}
	if (i < size)
	{
		if (i > size)
			i += size - 1;
		else
			i += ft_strlcpy(dst, src, size - i);
	}
	else
		i += ft_strlen(src);
	return (i);
}
