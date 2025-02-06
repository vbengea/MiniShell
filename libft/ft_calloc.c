/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:26:48 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/06 00:37:21 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	bytes;
	void	*mem;

	bytes = nmemb * size;
	if (size > bytes && nmemb > bytes)
		return (NULL);
	mem = malloc(bytes);
	if (mem)
		ft_bzero(mem, bytes);
	return (mem);
}

void	clear_arr_of_strs(char **sp)
{
	char	**p;
	char	*str;

	p = sp;
	if (sp != NULL)
	{
		while (*p)
		{
			str = *p;
			free(str);
			p++;
		}
		free(sp);
	}
}

char **copy_arr_of_strs(char **p, int len, int purge)
{
	int		i;
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
		i = 0;
		while (p && p[i])
		{
			arr[i] = ft_strdup(p[i]);
			if (!arr[i])
			{
				clear_arr_of_strs(arr);
				if (purge)
					clear_arr_of_strs(p);
				return (NULL);
			}
			i++;
		}
		// while (i < len)
		// 	arr[i++] = ft_strdup(" ");
		arr[len] = NULL;
	}
	if (purge)
		clear_arr_of_strs(p);
	return (arr);
}

char **add_arr_of_strs(char **p, char *str)
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
		arr[len] = ft_strdup(str);
	return (arr);
}

static	void swap_str(char **str, int i, int j) {
	char 	*s;

	s = str[i];
	str[i] = str[j];
	str[j] = s;
}

void sort_arr_of_strs(char **str, int order_type) {
    int		i;
	int		j;

	i = 0;
    while (str[i])
	{
        j = 0;
        while (str[j])
		{
            if ((order_type == 1) && (ft_strcmp(str[i], str[j]) < 0)) 
				swap_str(str, i, j);
			else if ((order_type == 0) && (ft_strcmp(str[i], str[j]) > 0)) 
                swap_str(str, i, j);
            j++;
        }
        i++;
    }
}