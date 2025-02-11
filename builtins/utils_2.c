/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/11 18:43:29 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	char	*interpolate(char *str, char **env)
{
	char	*cmp;
	char	*s;
	char	*r;
	int		i;

	r = NULL;
	cmp = ft_calloc(1, ft_strlen(str) + 1);
	if (cmp && str)
	{
		r = ft_strdup("");
		if (r)
		{
			i = 0;
			while (str[i] && str[i] != 39 && str[i] != ' ')
			{
				cmp[i] = str[i];
				i++;
			}
			s = get_env((cmp + 1), env);
			if (s)
				r = ft_stradd(r, s);
		}
		free(cmp);
	}
	return (r);
}

char	*interpolation(char *words, char **env)
{
	int		j;
	char	*inter;
	char	*parsed_word;

	j = 0;
	parsed_word = ft_strdup(" ");
	if (parsed_word)
	{
		while (words && words[j])
		{
			if (words[j] == '$')
			{
				inter = interpolate((words + j), env);
				if (inter)
				{
					if (j == 0 && *inter)
					{
						parsed_word[0] = inter[0];
						parsed_word = ft_stradd(parsed_word, (inter + 1));
					}
					else
						parsed_word = ft_stradd(parsed_word, inter);
					while (words[j] && words[j] != 39 && words[j] != ' ')
						j++;
					free(inter);
					continue ;
				}
			}
			else
				parsed_word = ft_charadd(words[j], parsed_word, j);
			j++;
		}
	}
	return (parsed_word);
}

char	**expantion(char *str, char **args)
{
	int		found;
	t_list	*lst;
	t_list	*p;

	found = 0;
	lst = ft_wildcard(str);
	while (lst)
	{
		p = lst;
		if (lst->content)
		{
			args = add_arr_of_strs(args, (char *)lst->content);
			found = 1;
			free(lst->content);
		}
		if (lst->next == NULL)
		{
			free(p);
			break ;
		}
		lst = lst->next;
		free(p);
	}
	if (!found)
		args = add_arr_of_strs(args, str);
	return (args);
}
