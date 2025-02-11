/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/07 03:11:13 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

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

t_redirection	*ft_lstred(t_redirection *node)
{
	t_redirection	*lst;

	lst = malloc(sizeof(t_redirection));
	if (lst)
	{
		lst->file = node->file;
		lst->type = node->type;
		lst->otype = node->otype;
		lst->next = NULL;
	}
	return (lst);
}

void	reverse_redirections(t_redirection *lst, t_redirection **rev)
{
	redlist_add(rev, ft_lstred(lst));
	if(lst->next)
		reverse_redirections(lst->next, rev);
}

void	print_redirs(void *content)
{
	char *str;

	str = (char *) content;
	printf("(%s) ", str);
}

void	ft_rediter(t_redirection *lst, void (*f)(t_redirection *))
{
	while (lst)
	{
		(*f)(lst);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}

int		has_outward_redirection(t_ast_node *ast)
{
	t_redirection	*lst;
	int				has_redirect;
	int				flags;
	int				fd;

	has_redirect = 0;
	lst = ast->redirs;
	while (lst)
	{
		if (lst->type == REDIRECT_OUT || lst->type == REDIRECT_APPEND)
		{
			has_redirect = 1;
			flags = O_WRONLY | O_CREAT | O_TRUNC;
			if (lst->type == REDIRECT_APPEND)
				flags = O_WRONLY | O_CREAT | O_APPEND;
			fd = open(lst->file, flags, 0666);
			if (fd >= 0)
				close(fd);
		}
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (has_redirect);
}

int		has_inward_redirection(t_redirection *lst)
{
	while (lst)
	{
		if (lst->type == REDIRECT_IN || lst->type == REDIRECT_HEREDOC)
			return (1);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (0);
}

int	has_group_redirection(t_ast_node *ast, int is_infile)
{
	t_ast_node	*node;

	node = ast;
	while (ast)
	{
		if (ast->parent == NULL)
			break ;
		ast = ast->parent;
		if (ast->type == NODE_GROUP && ast->redirs)
		{
			if (is_infile)
			{
				if (ast->in_fd >= 0)
				{
					node->in_fd = ast->in_fd;
					node->has_group_in_fd = 1;
					return (1);
				}
			}
			else
			{
				if (ast->out_fd >= 0)
				{
					node->out_fd = ast->out_fd;
					node->has_group_out_fd = 1;
					return (1);
				}
			}
		}
	}
	return (0);
}