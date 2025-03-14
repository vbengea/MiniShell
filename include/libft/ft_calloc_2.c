/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:26:48 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/23 15:19:53 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	copy_arr_inner(char **arr, char **p, int purge, int len)
{
	int	i;

	i = 0;
	while (p && p[i])
	{
		arr[i] = ft_strdup(p[i]);
		if (!arr[i])
		{
			clear_arr_of_strs(arr);
			if (purge)
				clear_arr_of_strs(p);
			return (0);
		}
		i++;
	}
	while (i < len)
		arr[i++] = ft_strdup(" ");
	arr[len] = NULL;
	return (1);
}

char	**copy_arr_of_strs(char **p, int len, int purge)
{
	char	**arr;

	if (len == 0)
	{
		len = 0;
		while (p[len])
			len++;
	}
	arr = malloc(sizeof(char *) * (len + 1));
	if (arr)
	{
		if (!copy_arr_inner(arr, p, purge, len))
			return (NULL);
	}
	if (purge)
		clear_arr_of_strs(p);
	return (arr);
}

char	**add_arr_of_strs(char **p, char *str)
{
	int		len;
	char	**arr;

	len = 0;
	if (!p)
		return (NULL);
	while (p[len])
		len++;
	arr = copy_arr_of_strs(p, len + 1, 1);
	if (str && arr && arr[len])
	{
		free(arr[len]);
		arr[len] = ft_strdup(str);
	}
	return (arr);
}

char	*ft_stradd(char *a, char *b)
{
	char	*t;

	t = a;
	a = ft_strjoin(a, b);
	free(t);
	return (a);
}

char	*ft_charadd(char c, char *word, int j)
{
	char	*charstr;

	if (j == 0)
		word[0] = c;
	else
	{
		charstr = malloc(2);
		charstr[0] = c;
		charstr[1] = '\0';
		word = ft_stradd(word, charstr);
		free(charstr);
	}
	return (word);
}
