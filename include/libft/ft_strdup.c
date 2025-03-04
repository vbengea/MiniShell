/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 02:00:19 by juandanielf       #+#    #+#             */
/*   Updated: 2024/09/23 12:17:28 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*s;

	i = 0;
	while (src[i])
		i++;
	s = malloc(sizeof(char) * i + 1);
	if (s == NULL)
	{
		return (NULL);
	}
	else
	{
		ft_strlcpy(s, src, i + 1);
		return (s);
	}
}
