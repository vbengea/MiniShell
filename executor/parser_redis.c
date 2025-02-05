/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/05 15:34:23 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void	build_redirect_node(t_ast_node *ast, t_redirect_params *p, char *file)
{
	t_redirection	*lst;

	lst = redlist_new((void *)file);
	redlist_add(&(ast->redirs), lst);
	lst->type = REDIRECT_NONE;
	if (p->ri == 1)
		lst->type = REDIRECT_IN;
	else if (p->ri == 2)
		lst->type = REDIRECT_HEREDOC;
	else if (p->ro == 1)
		lst->type = REDIRECT_OUT;
	else if (p->ro == 2)
		lst->type = REDIRECT_APPEND;
	if (p->prefix == 1 && p->suffix == -1)
		lst->otype = STDOUT_FILE;
	else if (p->prefix == 2 && p->suffix == -1)
		lst->otype = STDERR_FILE;
	else if (p->prefix == 1 && p->suffix == 2)
		lst->otype = STDOUT_STDERR;
	else if (p->prefix == 2 && p->suffix == 1)
		lst->otype = STDERR_STDOUT;
}

static	int	capture_redirection(t_ast_node *ast, char *str)
{
	int					i = 0;
	int					j = 0;
	char				*file;
	t_redirect_params 	p;

	p.ri = 0;
	p.ro = 0;
	p.prefix = -1;
	p.suffix = -1;
	if (str[i] == '0' || str[i] == '1' || str[i] == '2')
	{
		p.prefix = str[i] - '0';
		i++;
	}
	if (str[i] == '<')
	{
		i++;
		p.ri++;
	}
	else if (str[i] == '>')
	{
		i++;
		p.ro++;
	}
	if (str[i] == '<')
	{
		i++;
		p.ri++;
	}
	else if (str[i] == '>')
	{
		i++;
		p.ro++;
	}
	if (str[i] == '&')
	{
		i++;
		if (str[i] == '1' || str[i] == '2')
		{
			file = ft_strdup(" ");
			p.suffix = str[i] - '0';
			i++;
		}
		else
		{		
			perror("minishell: syntax error near unexpected token `&'");
			return (0);
		}
	}
	else
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		j = i;
		while (str[j] && !ft_isspace(str[j]))
			j++;
		if ((j - i) == 0)
			return (0);
		file = ft_substr(str, i, j - i);
		if (!file)
			return (0);
		i = j;
	}
	build_redirect_node(ast, &p, file);
	return (i);
}

char *parse_redirections(t_ast_node *ast, char *str)
{
	int		i;
	int		j;
	char	*s;
	char	*p;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		j = 0;
		if (str[i] == '<' || str[i] == '>')
		{
			if (i > 0 && (str[i - 1] == '0' || str[i - 1] == '1' || str[i - 1] == '2'))
			{
				p = (str + i - 1);
				j = capture_redirection(ast, p) - 1;
			}
			else
			{
				p = (str + i);
				j = capture_redirection(ast, p);
			}
			if (i > 0 && j > 0 && (str[i - 1] == '0' || str[i - 1] == '1' || str[i - 1] == '2'))
				str[i - 1] = ' ';
			j += i;
			while (i < j)
				str[i++] = ' ';
			continue ;
		}
		i++;
	}
	s = ft_strtrim(str, " ");
	return (s);
}

t_redirection	*redlist_new(void *content)
{
	t_redirection	*lst;

	lst = malloc(sizeof(t_redirection));
	if (lst)
	{
		lst->file = content;
		lst->next = NULL;
	}
	return (lst);
}

void	redlist_add(t_redirection **lst, t_redirection *new)
{
	t_redirection	*tmp;

	tmp = *lst;
	*lst = new;
	(*lst)->next = tmp;
}

void	redlist_iter(t_redirection *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->file);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}

void	print_redirs(void *content)
{
	char *str;

	str = (char *) content;
	printf("(%s) ", str);
}
