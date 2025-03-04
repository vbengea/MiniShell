/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:26:28 by juaflore          #+#    #+#             */
/*   Updated: 2024/09/28 12:53:27 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*tmp;

	tmp = malloc(n);
	if (dest == src || !n)
		return (dest);
	if (tmp != NULL)
	{
		ft_memcpy(tmp, src, n);
		ft_memcpy(dest, tmp, n);
		free(tmp);
	}
	return (dest);
}
