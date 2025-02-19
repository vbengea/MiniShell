/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/19 18:08:38 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	free_redirections(t_redirection *lst)
{
	t_redirection	*p;

	while (lst)
	{
		if (lst->file)
			free(lst->file);
		p = lst;
		if (lst->next)
			lst = lst->next;
		else
			lst = NULL;
		free(p);
	}
}

void	free_redirect_ast(t_ast_node *ast, int find_root)
{
	if (find_root)
		while (ast->parent)
			ast = ast->parent;
	if (ast)
	{
		if (ast->left)
			free_redirect_ast(ast->left, 0);
		if (ast->right)
			free_redirect_ast(ast->right, 0);
		if (ast->args)
			clear_arr_of_strs(ast->args);
		if (ast->redirs)
			free_redirections(ast->redirs);
		free(ast);
	}
}

void	cleanup(char *err, int code, t_ast_node *node, t_terminal *tty)
{
	if (err == NULL)
		perror(err);
	if (node)
	{
		free_redirect_ast(node, 1);
	}
	if (tty)
	{
		destroy_terminal(tty);
	}
	exit(code);
}

int	is_last(t_ast_node *node, t_terminal *tty)
{
	(void) tty;
	node = node->parent;
	while (node)
	{
		if (node->type == NODE_PIPE && node->discovered == 0)
			return (0);
		node = node->parent;
	}
	return (1);
}

int	is_builtin(t_ast_node *node)
{
	char	**b;
	int		i;
	int		r;

	r = 0;
	b = ft_split("cd echo env exit export pwd unset", ' ');
	if (b)
	{
		if (node->args[node->args_index] == NULL)
			r = 1;
		if (node->type == NODE_CMND && node->args)
		{
			i = 0;
			while (r == 0 && b[i])
			{
				if (ft_cmpexact(node->args[node->args_index], b[i]))
					r = 1;
				i++;
			}
		}
		clear_arr_of_strs(b);
	}
	return (r);
}
