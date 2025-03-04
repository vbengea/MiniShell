/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juandanielflores <juandanielflores@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:14:02 by juaflore          #+#    #+#             */
/*   Updated: 2024/09/21 14:27:22 by juandanielf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char		*ss;
	signed char	ch;

	ch = c;
	ss = (char *) s;
	while (*ss)
	{
		if (*ss == ch)
			return (ss);
		ss++;
	}
	if (*ss == ch)
		return (ss);
	return (NULL);
}
