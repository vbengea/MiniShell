/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/25 16:49:17 by juaflore         ###   ########.fr       */
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

void	print_redirs(void *content)
{
	char *str;

	str = (char *) content;
	printf("(%s) ", str);
}

void	ast_printer(t_ast_node *ast, int level)
{
	int i = 0;

	while (i++ < level)
		printf("  ");
	if (ast->type == NODE_CMND)
	{
		printf("TYPE: %d\t\tARGS: ", ast->type);
		i = 0;
		while (ast->args[i])
			printf("%s ", ast->args[i++]);
		printf("\tREDIRS: ");
		redlist_iter(ast->redirs, print_redirs);
		printf("\n");
	}
	else
		printf("TYPE: %d\n", ast->type);
	if (ast->left)
		ast_printer(ast->left, level + 1);
	if (ast->right)
		ast_printer(ast->right, level + 1);
}