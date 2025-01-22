/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:26:40 by juaflore          #+#    #+#             */
/*   Updated: 2024/09/28 12:41:07 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	j;
	unsigned char	a;
	unsigned char	b;
	char			*z1;
	char			*z2;

	j = 0;
	z1 = (char *)s1;
	z2 = (char *)s2;
	while (j < n)
	{
		a = *z1++;
		b = *z2++;
		if (a != b)
			return (a - b);
		j++;
	}
	return (0);
}
