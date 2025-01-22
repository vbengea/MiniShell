/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juandanielflores <juandanielflores@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:26:01 by juaflore          #+#    #+#             */
/*   Updated: 2024/09/22 21:12:12 by juandanielf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*bytes;
	size_t			i;

	bytes = (unsigned char *)s;
	i = 0;
	while (i < n)
		bytes[i++] = c;
	return (s);
}
