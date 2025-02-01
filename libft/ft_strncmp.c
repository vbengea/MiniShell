/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:17:55 by juaflore          #+#    #+#             */
/*   Updated: 2024/09/28 12:41:25 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	j;
	unsigned char	a;
	unsigned char	b;

	j = 0;
	while (j < n)
	{
		a = *s1++;
		b = *s2++;
		if (a != b)
			return (a - b);
		if (a == '\0' && b != '\0')
			return (-1);
		else if (a != '\0' && b == '\0')
			return (1);
		else if (a == '\0' && b == '\0')
			return (0);
		j++;
	}
	return (0);
}


int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	j;
	unsigned char	a;
	unsigned char	b;
	unsigned int	n;

	j = 0;
	n = ft_strlen(s1);
	while (j < n)
	{
		a = *s1++;
		b = *s2++;
		if (a != b)
			return (a - b);
		if (a == '\0' && b != '\0')
			return (-1);
		else if (a != '\0' && b == '\0')
			return (1);
		else if (a == '\0' && b == '\0')
			return (0);
		j++;
	}
	return (0);
}
