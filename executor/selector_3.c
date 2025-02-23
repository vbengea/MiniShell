/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:49:26 by jflores           #+#    #+#             */
/*   Updated: 2025/02/23 13:44:29 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	parse_command(t_ast_node *node, t_terminal *tty)
{
	int		i;
	char	*str;
	char	**args;

	if (node->type == NODE_CMND && node->args[0] != NULL)
	{
		i = node->args_index;
		args = ft_split(" ", ' ');
		while (node->args[i])
		{
			if (node->expand_flag[i] == 1)
				parse_command_master(node, i, &args, tty);
			else
			{
				str = node->args[i];
				args = expantion(str, args, node);
			}
			i++;
		}
		clear_arr_of_strs(node->args);
		node->args = args;
	}
}

void	preexecute(t_ast_node *node, t_terminal *tty)
{
	if (node->args_index == 0)
	{
		parse_command(node, tty);
		detect_in_redirection(node, 0, tty);
		detect_out_redirection(node, tty);
	}
}

void	postexecute(t_ast_node *node, t_terminal *tty)
{
	char	*file;

	multiple_output_redirections(node, tty);
	file = tmp_path(node->nid, REDIRECT_IN, node, tty);
	if (file)
	{
		if (access(file, F_OK) == 0)
			unlink(file);
		free(file);
	}
	if (node->in_fd >= 0 && node->has_group_in_fd == 0)
	{
		close(node->in_fd);
		node->in_fd = -1;
	}
	if (node->out_fd >= 0 && node->has_group_out_fd == 0)
	{
		close(node->out_fd);
		node->out_fd = -1;
	}
}

void	navigator_init(t_ast_node *node, t_terminal *tty)
{
	if (node->left)
	{
		node->left->parent = node;
		node->left->side = 0;
		node->left->parent_type = node->type;
		selector(node->left, tty);
	}
	if (node->right)
	{
		node->right->parent = node;
		node->right->side = 1;
		node->right->parent_type = node->type;
		selector(node->right, tty);
	}
}
