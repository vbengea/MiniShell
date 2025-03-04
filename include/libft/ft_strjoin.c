/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juandanielflores <juandanielflores@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:50:18 by juandanielf       #+#    #+#             */
/*   Updated: 2024/09/19 00:56:44 by juandanielf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(len);
	if (str)
	{
		str[0] = '\0';
		ft_strlcat(str, s1, len);
		ft_strlcat(str, s2, len);
	}
	return (str);
}
