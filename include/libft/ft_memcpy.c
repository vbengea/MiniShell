/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:26:22 by juaflore          #+#    #+#             */
/*   Updated: 2024/09/28 12:52:41 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*bytes_src;
	unsigned char	*bytes_dst;

	i = 0;
	bytes_src = (unsigned char *)src;
	bytes_dst = (unsigned char *)dest;
	if (dest == src || !n)
		return (dest);
	while (i < n)
	{
		bytes_dst[i] = bytes_src[i];
		i++;
	}
	return (dest);
}
