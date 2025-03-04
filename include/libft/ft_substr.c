/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:52:46 by juandanielf       #+#    #+#             */
/*   Updated: 2024/09/23 11:36:43 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		sz;

	sz = ft_strlen(s);
	if (start >= sz)
		len = 0;
	else if (start + len > sz)
		len = sz - start;
	str = malloc(len + 1);
	if (str)
	{
		if (start > sz)
			ft_strlcpy(str, "", len + 1);
		else
			ft_strlcpy(str, (s + start), len + 1);
	}
	return (str);
}
