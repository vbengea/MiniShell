/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/07 03:59:50 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	ast_printer(t_ast_node *ast, int level)
{
	int i = 0;

	if (ast)
	{
		while (i++ < level)
			printf("  ");
		if (ast->type == NODE_CMND || ast->type == NODE_GROUP)
		{
			printf("TYPE: %d [NID:%d] [SIDE:%d] [ARGS]: ", ast->type, ast->nid, ast->side);
			i = 0;
			while (ast->args && ast->args[i])
				printf("%s ", ast->args[i++]);
			printf("[REDIRS]: ");
			if (ast->redirs)
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
}

t_ast_node	*get_node_by_token(t_mini_token token)
{
	t_ast_node	*ast;

	ast = NULL;
	if (token == AND)
		ast = create_ast_node(NODE_AND, NULL);
	if (token == OR)
		ast = create_ast_node(NODE_OR, NULL);
	else if (token == PIPE)
		ast = create_ast_node(NODE_PIPE, NULL);
	else if (token == SUBSHELL)
		ast = create_ast_node(NODE_GROUP, NULL);
	else if (token == COMMAND)
		ast = create_ast_node(NODE_CMND, NULL);
	return (ast);
}

int	is_node(char *context, char *term)
{
	return (ft_strncmp(context, term, ft_strlen(term)) == 0);
}

int	is_control_character(char *context)
{
	return (is_node(context, "&&") || \
			is_node(context, "||") || \
			is_node(context, "|"));
}

int	ff_subcontext(char *context)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	if (context[i] == '(')
	{
		while (context[i])
		{
			if (context[i] == '(')
				p++;
			else if (context[i] == ')')
				p--;
			if (p == 0)
				break ;
			i++;
		}
		if (p > 0)
			return (1);
	}
	else if (context[i] == 34)
	{
		i++;
		while (context[i] != 34)
			i++;
	}
	else if (context[i] == 39)
	{
		i++;
		while (context[i] != 39)
			i++;
	}
	return (i + 1);
}

