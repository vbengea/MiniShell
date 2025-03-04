/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juandanielflores <juandanielflores@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:23:46 by juandanielf       #+#    #+#             */
/*   Updated: 2024/09/22 14:50:19 by juandanielf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	size_t				len;
	char				*str;

	i = 0;
	len = ft_strlen(s);
	str = malloc(len + 1);
	if (str != NULL)
	{
		while (i < len)
		{
			str[i] = f(i, s[i]);
			i++;
		}
		str[len] = '\0';
	}
	return (str);
}
