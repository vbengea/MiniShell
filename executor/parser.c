/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/05 15:41:29 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

t_ast_node	*create_node_command(char *context, t_redirection *redirs, int *index)
{
	t_ast_node	*ast;
	char		**elements;
	char		*cmd;
	char		*args;
	int			len;

	(void) redirs;
	ast = create_ast_node(NODE_CMND, NULL);
	ast->fd = -1;
	context = parse_redirections(ast, context);
	// if (!ast->redirs && redirs)
	// 	ast->redirs = redirs;
	elements = ft_split(context, ' ');
	cmd = elements[0];
	len = ft_strlen(cmd);
	args = ft_strtrim((context + len), " ");
	ast->args = elements;
	ast->nid = *index;
	*index = *index + 1;
	free(args);
	return (ast);
}

t_ast_node	*create_group_command(char *context, t_redirection *redirs, int *index)
{
	t_ast_node	*ast;
	int			i;
	int			j;
	char		*reds;
	char		*pars;
	int			p;
	int			len;

	ast = NULL;
	i = 0;
	p = 0;
	while (ft_isspace(context[i]))
		i++;
	context = (context + i);
	ast = get_node_by_token(SUBSHELL);
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
		if (reds[i] == '(')
			p++;
		else if(reds[i] == ')')
		{
			p--;
			reds[i] = ' ';
		}
		if (p > 0)
		{
			pars[j++] = reds[i];
			reds[i] = ' ';
		}
		i++;
	}
	parse_redirections(ast, reds);
	if (!ast->redirs && redirs)
		ast->redirs = redirs;
	ast->left = create_structure((pars + 1), AND, ast->redirs, index);
	free(reds);
	free(pars);
	return (ast);
}

static	t_ast_node	*get_execution_node(char *context, t_mini_token level, t_redirection *redirs, int *index)
{
	t_ast_node	*ast;
	int			i;
	int			j;

	ast = NULL;
	i = 0;
	if (level == AND)
		ast = create_structure(context, PIPE, redirs, index);
	else
	{
		while (ft_isspace(context[i]))
			i++;
		j = i;
		while (context[j])
		{
			if (context[j] == '(')
				return create_group_command(context, redirs, index);
			j++;
		}
		context = (context + i);
		ast = create_node_command(context, redirs, index);
	}
	return (ast);
}

static	void	inner(t_ast_node **ast, char *s, int *i, int *k, int level, t_redirection *redirs, int *index)
{
	t_ast_node	*nod;

	if (is_node((s + *i), "&&"))
		nod = get_node_by_token(AND);
	else if (is_node((s + *i), "||"))
		nod = get_node_by_token(OR);
	else
		nod = get_node_by_token(PIPE);
	if (*ast == NULL)
	{
		*ast = nod;
		(*ast)->left = get_execution_node(ft_substr(s, *k, *i - *k), level, redirs, index);
	}
	else
	{
		nod->left = *ast;
		(*ast)->right = get_execution_node(ft_substr(s, *k, *i - *k), level, redirs, index);
		*ast = nod;
	}
	*i += 2;
	*k = *i;
}

t_ast_node	*create_structure(char *context, t_mini_token level, t_redirection *redirs, int *index)
{
	t_ast_node	*ast;
	int			i;
	int			k;

	i = 0;
	k = 0;
	ast = NULL;
	while (context[i])
	{
		if (ft_isquote(context[i]) || context[i] == '(')
			i += ff_subcontext((context + i));
		else if (is_control_character((context + i)))
			inner(&ast, context, &i, &k, level, redirs, index);
		else
			i++;
	}
	if (ast == NULL)
		ast = get_execution_node(ft_substr(context, k, i - k), level, redirs, index);
	else
	{
		ast->right = get_execution_node(ft_substr(context, k, i - k), level, redirs, index);
		ast->right->side = 1;
	}
	return (ast);
}

t_ast_node	*build_redirect_ast(char *context)
{
	t_ast_node	*ast;
	int			index;

	index = 1;
	ast = create_structure(context, AND, NULL, &index);
	// ast_printer(ast, 0);
	return (ast);
}
