/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/04 10:49:57 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void		clean_quotes(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			j = 0;
			while (str[i + j])
			{
				str[i + j] = str[i + j + 1];
				j++;
			}
		}
		i++;
	}
}

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

char	*interpolation(char *str, char **env)
{
	int		j;
	char	**s;
	char	*r;

	clean_quotes(str);
	s = ft_split(str, ' ');
	r = ft_strdup("");
	if (s)
	{
		j = 0;
		while (s[j])
		{
			if (s[j][0] == '$')
			{
				str = get_env((s[j] + 1), env);
				if (str)
					r = add_str(r, str);
				else
					r = add_str(r, " ");
			}
			else
				r = add_str(r, s[j]);
			j++;
		}
		clear_arr_of_strs(s);
	}
	return (r);
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

void	check_shlvl(t_ast_node *node, char ***env)
{
	int		l;
	char	*lvl;

	if (ft_strncmp(node->args[0], "minishell", 9) == 0 && ft_strlen(node->args[0]) == 9)
	{
		lvl = getenv("SHLVL");
		l = ft_atoi(lvl) + 1;
		lvl = ft_itoa(l);
		*env = set_env("SHLVL", lvl, *env);
		free(lvl);
	}
}

void		echo_bi(t_ast_node *node, char **env)
{
	int		i;
	char	*str;
	char	*p;
	char 	**params;

	params = node->args;
	i = 1;
	while (params[i])
	{
		str = interpolation(params[i], env);
		if (node->out_fd < 0)
			printf("%s ", str);
		else
		{
			p = ft_strjoin(str, " ");
			ft_putstr_fd(p, node->out_fd);
			free(p);
		}
		free(str);
		i++;
	}
	if (node->out_fd < 0)
		printf("\n");
	else
		ft_putchar_fd('\n', node->out_fd);
}
