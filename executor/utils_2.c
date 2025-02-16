/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:49:12 by jflores           #+#    #+#             */
/*   Updated: 2025/02/16 11:17:00 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

int	is_pipe_state(t_ast_node *node)
{
	if (node->parent_type == NODE_PIPE)
		return (1);
	return (0);
}

static	int	is_identifier(char c)
{
	if (c && c != 39 && (ft_isalnum(c) || c == '_' || c == '?'))
		return (1);
	else
		return (0);
}

void	ast_printer(t_ast_node *ast, int level)
{
	int	i;

	if (ast)
	{
		i = 0;
		while (i++ < level)
			printf("  ");
		if (ast->type == NODE_CMND || ast->type == NODE_GROUP)
		{
			printf("[TYPE:%d] [NID:%d] [SIDE:%d] [ARGS]: ", ast->type, \
				ast->nid, ast->side);
			i = 0;
			while (ast->args && ast->args[i])
			{
				printf("_%s_(%d, %d),", ast->args[i], ast->expand_flag[i], \
					ast->has_space[i]);
				i++;
			}
			printf("[REDIRS]: ");
			if (ast->redirs)
				redlist_iter(ast->redirs, print_redirs);
			printf("\n");
		}
		else
			printf("[TYPE: %d] [NID:%d] [SIDE:%d] \n", ast->type, ast->nid, \
				ast->side);
		if (ast->left)
			ast_printer(ast->left, level + 1);
		if (ast->right)
			ast_printer(ast->right, level + 1);
	}
}

void	print_redirs(void *content, int flag)
{
	char	*str;

	str = (char *) content;
	printf("(%s [%d]) ", str, flag);
}

void	redlist_iter(t_redirection *lst, void (*f)(void *, int x))
{
	while (lst)
	{
		(*f)(lst->file, lst->is_quote);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
}
