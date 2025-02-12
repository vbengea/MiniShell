/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/12 18:47:53 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	free_redirect_ast(t_ast_node *ast, int find_root)
{
	t_redirection	*lst;
	t_redirection	*p;

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
		{
			lst = ast->redirs;
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
		free(ast);
	}
}

void	cleanup(char *err)
{
	perror(err);
	exit(1);
}

int	is_last(t_ast_node *node, int files[3])
{
	(void) files;
	node = node->parent;
	while (node)
	{
		if(node->type == NODE_PIPE && node->discovered == 0)
			return (0);
		node = node->parent;
	}
	return (1);
}

int    is_builtin(t_ast_node *node)
{
	char	*b[8] = { "cd", "echo", "env", "exit", "export", "pwd", "unset", NULL };
	int		i = 0;

	if (node->type == NODE_CMND && node->args)
	{
		while (b[i])
		{
			if ((ft_strncmp(node->args[0], b[i], ft_strlen(b[i])) == 0)
				&& (ft_strlen(b[i]) == ft_strlen(node->args[0])))
				return (1);
			i++;
		}
	}
	return (0);
}

int    is_pipe_state(t_ast_node *node)
{
	if (node->parent_type == NODE_PIPE)
		return (1);
	return (0);
}
