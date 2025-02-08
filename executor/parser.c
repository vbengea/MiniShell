/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/07 04:00:33 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	nid(t_ast_node *ast, int *index)
{
	ast->nid = *index;
	*index = *index + 1;
}

t_ast_node	*create_node_command(char *context, int *index)
{
	t_ast_node	*ast;
	char		**elements;

	ast = create_ast_node(NODE_CMND, NULL);
	context = parse_redirections(ast, context);
	elements = ft_split(context, ' ');
	ast->args = elements;
	nid(ast, index);
	return (ast);
}

t_ast_node	*create_group_command(char *context, int *index)
{
	t_ast_node	*ast;
	int			i;
	int			j;
	char		*reds;
	char		*pars;
	char		*clear;
	int			p;
	int			len;
	char		c;
	bool		parse;

	ast = NULL;
	i = 0;
	p = 0;
	parse = false;
	while (ft_isspace(context[i]))
		i++;
	context = (context + i);
	ast = get_node_by_token(SUBSHELL);
	nid(ast, index);
	reds = ft_strdup(context);
	len = ft_strlen(reds);
	pars = malloc(len + 1);
	pars[len] = '\0';
	i = 0;
	while (i < len)
		pars[i++] = ' ';
	i = 0;
	j = 0;
	while (reds[i])
	{
		c = reds[i];
		if (reds[i] == '(')
		{
			if (p == 0)
				reds[i] = ' ';
			p++;
		}
		else if(reds[i] == ')')
		{
			p--;
			if (p == 0)
			{
				reds[i] = ' ';
				parse = false;
			}
		}
		if (p > 0 && parse)
		{
			pars[j++] = c;
			reds[i] = ' ';
		}
		if (p > 0)
			parse = true;
		i++;
	}
	clear = reds;
	reds = ft_strtrim(reds, " ");
	free(clear);
	clear = pars;
	pars = ft_strtrim(pars, " ");
	free(clear);
	parse_redirections(ast, reds);
	ast->left = create_structure(pars, AND, index);
	ast->left->parent = ast;
	free(reds);
	free(pars);
	return (ast);
}

static	t_ast_node	*get_execution_node(char *context, t_mini_token level, int *index)
{
	t_ast_node	*ast;
	int			i;
	int			j;

	ast = NULL;
	i = 0;
	if (level == AND)
		ast = create_structure(context, PIPE, index);
	else
	{
		while (ft_isspace(context[i]))
			i++;
		j = i;
		while (context[j])
		{
			if (context[j] == '(')
				return create_group_command(context, index);
			j++;
		}
		context = (context + i);
		ast = create_node_command(context, index);
	}
	return (ast);
}

static	void	inner(t_ast_node **ast, char *s, int *i, int *k, int level, int *index)
{
	t_ast_node	*nod;
	char		*t;

	nod = NULL;
	if (is_node((s + *i), "&&") && (level == AND || level == OR))
		nod = get_node_by_token(AND);
	else if (is_node((s + *i), "||") && (level == AND || level == OR))
		nod = get_node_by_token(OR);
	else if (level == PIPE)
		nod = get_node_by_token(PIPE);
	else
		perror("Syntax error\n");
	if (nod)
	{
		nid(nod, index);
		if (*ast == NULL)
		{
			*ast = nod;
			t = ft_substr(s, *k, *i - *k);
			(*ast)->left = get_execution_node(t, level, index);
			(*ast)->left->parent = (*ast);
			free(t);
		}
		else
		{
			nod->left = *ast;
			t = ft_substr(s, *k, *i - *k);
			(*ast)->right = get_execution_node(t, level, index);
			(*ast)->right->side = 1;
			(*ast)->right->parent = (*ast);
			*ast = nod;
			free(t);
		}
	}
	*i += 2;
	*k = *i;
}

t_ast_node	*create_structure(char *context, t_mini_token level, int *index)
{
	t_ast_node	*ast;
	int			i;
	int			k;
	char		*s;

	i = 0;
	k = 0;
	ast = NULL;
	while (context[i])
	{
		if (ft_isquote(context[i]) || context[i] == '(')
			i += ff_subcontext(context + i);
		else 
		if (is_control_character(context + i, level))
			inner(&ast, context, &i, &k, level, index);
		else
			i++;
	}
	if (ast == NULL)
	{
		s = ft_substr(context, k, i - k);
		ast = get_execution_node(s, level, index);
		free(s);
	}
	else
	{
		s = ft_substr(context, k, i - k);
		ast->right = get_execution_node(s, level, index);
		ast->right->side = 1;
		ast->right->parent = ast;
		free(s);
	}
	return (ast);
}

t_ast_node	*build_redirect_ast(char *context)
{
	t_ast_node	*ast;
	int			index;

	index = 1;
	context = ft_strdup(context);
	ast = create_structure(context, AND, &index);
	ast_printer(ast, 0);
	free(context);
	return (ast);
}
