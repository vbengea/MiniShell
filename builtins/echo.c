/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/11 10:26:26 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*get_env(char *var, char **env)
{
	int	i;
	int len;

	i = 0;
	var = ft_strjoin(var, "=");
	len = ft_strlen(var);
	while (var && env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
		{
			free(var);
			return (env[i] + len);
		}
		i++;
	}
	free(var);
	return (NULL);
}

char	**set_env(char *key, char *value, char **env)
{
	int		i;
	int		found;
	int		len;
	char	*str;
	char	*var;

	i = 0;
	found = 0;
	var = key;
	var = ft_strjoin(var, "=");
	while (var && env[i])
	{
		if (var && ft_strncmp(env[i], var, ft_strlen(var)) == 0)
		{
			str = ft_strjoin(var, value);
			if (str)
			{
				free(env[i]);
				len = ft_strlen(str);
				env[i] = malloc(len + 1);
				if (env[i])
				{
					ft_strlcpy(env[i], str, len + 1);
					env[i][len] = '\0';
				}
				free(str);
			}
			found = 1;
			break ;
		}
		i++;
	}
	if (!found)
	{
		if (var)
		{
			str = ft_strjoin(var, value);
			if (str)
			{
				env = add_arr_of_strs(env, str);
				free(str);
			}
		}
	}
	free(var);
	return (env);
}

static	char *add_str(char *a, char *b)
{
	char	*t;

	t = a;
	a = ft_strjoin(a, b);
	free(t);
	return (a);
}

static	char *add_char(char c, char *word, int j)
{
	char	*charstr;

	(void) j;
	if (j == 0)
	{
		word[0] = c;
	}
	else
	{
		charstr = malloc(2);
		charstr[0] = c;
		charstr[1] = '\0';
		word = add_str(word, charstr);
		free(charstr);
	}
	return (word);
}

static	char	*interpolate(char *str, char **env)
{
	char	*cmp;
	char	*s;
	char	*r;
	int		i;

	r = NULL;
	cmp = calloc(1, ft_strlen(str) + 1);
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
				r = add_str(r, s);
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
	parsed_word = malloc(1);
	if (parsed_word)
	{
		parsed_word[0] = '\0';
		while (words && words[j])
		{
			if (words[j] == '$')
			{
				inter = interpolate((words + j), env);
				if (inter)
				{
					parsed_word = add_str(parsed_word, inter);
					while (words[j] && words[j] != 39 && words[j] != ' ')
						j++;
					free(inter);
					continue ;
				}
			}
			else
				parsed_word = add_char(words[j], parsed_word, j);
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

void	check_shlvl(char ***env)
{
	int		l;
	char	*lvl;

	lvl = getenv("SHLVL");
	l = ft_atoi(lvl) + 1;
	lvl = ft_itoa(l);
	*env = set_env("SHLVL", lvl, *env);
	free(lvl);
}

void		echo_bi(t_ast_node *node)
{
	int		i;
	char	*str;
	char	*p;
	char 	**params;

	params = node->args;
	i = 1;
	while (params[i])
	{
		str = params[i];
		if (node->out_fd < 0)
			printf("%s", str);
		else
		{
			p = ft_strjoin(str, "");
			ft_putstr_fd(p, node->out_fd);
			free(p);
		}
		i++;
	}
	if (node->out_fd < 0)
		printf("\n");
	else
		ft_putchar_fd('\n', node->out_fd);
}
