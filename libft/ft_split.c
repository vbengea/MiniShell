/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 02:00:50 by juandanielf       #+#    #+#             */
/*   Updated: 2024/09/28 15:00:19 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	word_count(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] == c)
			i++;
		j++;
	}
	if (j == 0)
		return (0);
	return (i + 1);
}

static	void	normalize(char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (j == 0)
				s[k++] = s[i];
			j++;
		}
		else
		{
			j = 0;
			s[k++] = s[i];
		}
		i++;
	}
	while (k < i)
		s[k++] = '\0';
}

static	char	*trim(char const *s, char c)
{
	char	sep[2];
	char	*str;

	str = NULL;
	sep[0] = c;
	sep[1] = '\0';
	str = ft_strtrim(s, sep);
	if (str)
		normalize(str, c);
	return (str);
}

static	int	split_word(char **ptr, char **lst, size_t ch[2], char *trimmed)
{
	size_t	j;
	size_t	i;
	char	a;

	i = ch[0];
	a = (char) ch[1];
	if (ptr)
	{
		j = 0;
		while ((*ptr)[j] && (*ptr)[j] != a)
			j++;
		lst[i] = ft_substr(*ptr, 0, j);
		if (lst[i])
			*ptr = (*ptr + j + 1);
		else
		{
			clear_arr_of_strs(lst);
			free(trimmed);
			return (0);
		}
	}
	ch[0] += 1;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**lst;
	char		*trimmed;
	char		*ptr;
	size_t		count;
	size_t		ch[2];

	lst = NULL;
	trimmed = trim(s, c);
	if (!trimmed)
		return (NULL);
	count = word_count(trimmed, c);
	ch[1] = c;
	lst = malloc(sizeof(char *) * (count + 1));
	if (lst)
	{
		ch[0] = 0;
		ptr = trimmed;
		while (lst && ch[0] < count && count > 0)
			if (!split_word(&ptr, lst, ch, trimmed))
				return (NULL);
		lst[count] = NULL;
	}
	free(trimmed);
	return (lst);
}
