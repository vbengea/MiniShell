/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:44:47 by juaflore          #+#    #+#             */
/*   Updated: 2024/09/30 09:36:32 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	set_offset_start(char const *s1, char const *set, \
	size_t	slen, t_splitter *sp)
{
	size_t	i;
	size_t	j;
	size_t	s;

	j = 0;
	while (j < slen)
	{
		i = 0;
		s = sp->start;
		while (i < sp->count)
		{
			if (s1[j] == set[i])
			{
				(sp->start)++;
				break ;
			}
			i++;
		}
		if (s == sp->start)
			break ;
		j++;
	}
}

static	void	set_offset_end(char const *s1, char const *set, \
	size_t	slen, t_splitter *sp)
{
	size_t	i;
	size_t	j;
	size_t	s;

	j = slen - 1;
	while (j != 0)
	{
		i = 0;
		s = sp->end;
		while (i < sp->count)
		{
			if (s1[j] == set[i] && sp->end > sp->start)
			{
				(sp->end)--;
				break ;
			}
			i++;
		}
		if (s == sp->end)
			break ;
		j--;
	}
}

static	void	set_offsets(char const *s1, char const *set,
	t_splitter *sp)
{
	size_t	slen;

	slen = ft_strlen(s1);
	if (sp->count > 0)
	{
		set_offset_start(s1, set, slen, sp);
		set_offset_end(s1, set, slen, sp);
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	t_splitter	sp;

	str = NULL;
	sp.start = 0;
	sp.end = ft_strlen(s1);
	sp.count = ft_strlen(set);
	if (sp.count > 0)
		set_offsets(s1, set, &sp);
	str = malloc(sp.end - sp.start + 1);
	if (str)
		ft_strlcpy(str, (s1 + sp.start), sp.end - sp.start + 1);
	return (str);
}
