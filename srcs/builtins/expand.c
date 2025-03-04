/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/03/04 19:06:44 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

char	*extract_variable(char *str, int *i, t_terminal *tty)
{
	char	*cmp;
	char	*s;
	char	*r;

	r = ft_strdup("");
	if (r)
	{
		cmp = ft_calloc(1, ft_strlen(str) + 1);
		if (cmp)
		{
			while (is_identifier(str[*i]))
			{
				cmp[*i] = str[*i];
				(*i)++;
			}
			s = get_env(NULL, -1, (cmp + 1), tty);
			if (s)
			{
				r = ft_stradd(r, s);
				free(s);
			}
			free(cmp);
		}
	}
	return (r);
}

char	*expand_variable(char *words, int *j, char *parsed_word, \
	t_terminal *tty)
{
	int		i;
	char	*inter;

	i = 1;
	if (words == NULL)
		return (parsed_word);
	inter = extract_variable((words + *j), &i, tty);
	if (inter)
	{
		if (*j == 0 && *inter)
		{
			parsed_word[0] = inter[0];
			parsed_word = ft_stradd(parsed_word, (inter + 1));
		}
		else
			parsed_word = ft_stradd(parsed_word, inter);
		*j += (i - 1);
		free(inter);
	}
	return (parsed_word);
}

char	*expand_diacritical(char *words, int *j, char *parsed_word, \
	t_terminal *tty)
{
	char	*s;

	s = get_env(NULL, -1, words, tty);
	if (s)
	{
		if (*j == 0 && *s)
		{
			parsed_word[0] = s[0];
			parsed_word = ft_stradd(parsed_word, (s + 1));
		}
		else
			parsed_word = ft_stradd(parsed_word, s);
		free(s);
	}
	return (parsed_word);
}

char	*interpolation(char *words, int arg_index, t_terminal *tty)
{
	int		j;
	char	*parsed_word;

	j = 0;
	(void) arg_index;
	parsed_word = ft_strdup(" ");
	if (parsed_word)
	{
		while (words && words[j])
		{
			if (words[j] == '~' && (!words[j + 1] || words[j + 1] == '/'))
				parsed_word = expand_diacritical("HOME", &j, parsed_word, tty);
			else if (words[j] == '$' && words[j + 1] && \
				!ft_isspace(words[j + 1]))
				parsed_word = expand_variable(words, &j, parsed_word, tty);
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
		if (lst->content)
		{
			args = add_arr_of_strs(args, (char *)lst->content);
			found = 1;
			free(lst->content);
		}
		if (lst->next == NULL)
			break ;
		p = lst;
		lst = lst->next;
		free(p);
	}
	if (lst)
		free(lst);
	if (!found)
		args = add_arr_of_strs(args, str);
	return (args);
}
