/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juandanielflores <juandanielflores@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:15:53 by juaflore          #+#    #+#             */
/*   Updated: 2024/09/21 22:15:44 by juandanielf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	signed char	ch;
	char		*p;

	p = NULL;
	ch = c;
	while (*s)
	{
		if (*s == ch)
			p = (char *)s;
		s++;
	}
	if (*s == ch)
		p = (char *)s;
	return (p);
}
