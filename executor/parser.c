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

static	t_ast_node	*get_execution_node(char *context, t_mini_token level)
{
	t_ast_node	*ast;
	char		*str;
	int			i;

	ast = NULL;
	if (level == AND)
		ast = create_structure(context, PIPE);
	else
	{
		i = 0;
		
		if(context[0] == '(')
		{
			str = ft_substr(context, 1, ff_subcontext(context) - 2);
			ast = get_node_by_token(SUBSHELL);
			ast->left = create_structure(str, AND);
			free(str);
		}
		else
			ast = create_node_command(context);
	}
	return (ast);
}

t_ast_node	*create_structure(char *context, t_mini_token level)
{
	t_ast_node	*ast;
	t_ast_node	*nod;
	int i = 0;
	int k = 0;

	ast = NULL;
	while (context[i])
	{
		if (ft_isquote(context[i]) || context[i] == '(')
			i += ff_subcontext((context + i));
		else if (is_control_character((context + i)))
		{
			if (is_node((context + i), "&&"))
				nod = get_node_by_token(AND);
			else if (is_node((context + i), "||"))
				nod = get_node_by_token(OR);
			else
				nod = get_node_by_token(PIPE);
			if (ast == NULL)
			{
				ast = nod;
				ast->left = get_execution_node(ft_substr(context, k, i - k), level);
				nod->left->side = 0;
			}
			else
			{
				nod->left = ast;
				nod->left->side = 0;
				ast->right = get_execution_node(ft_substr(context, k, i - k), level);
				ast->right->side = 1;
				ast = nod;
			}
			i += 2;
			k = i;
		}
		else
			i++;
	}
	if (ast == NULL)
		ast = get_execution_node(ft_substr(context, k, i - k), level);
	else
	{
		ast->right = get_execution_node(ft_substr(context, k, i - k), level);
		ast->right->side = 1;
	}
	return (ast);
}

t_ast_node	*build_redirect_ast(char *context)
{
	t_ast_node	*ast;
	
	ast = create_structure(context, AND);
	ast_printer(ast, 0);
	return (ast);
}
