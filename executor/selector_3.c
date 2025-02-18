/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:49:26 by jflores           #+#    #+#             */
/*   Updated: 2025/02/18 23:53:02 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	parse_command(t_ast_node *node, t_terminal *tty)
{
	int		i;
	int		j;
	char	*str;
	char	**args;
	char	**inter;

	if (node->type == NODE_CMND && node->args[0] != NULL)
	{
		i = node->args_index;
		args = ft_split(" ", ' ');
		while (node->args[i])
		{
			if (node->expand_flag[i] == 1)
			{
				str = interpolation(node->args[i], i, tty);
				inter = ft_split(str, ' ');
				free(str);
				if (inter)
				{
					j = 0;
					while (inter[j])
						j++;
					if (j > 1)
					{
						j = 0;
						while (inter[j])
						{
							if (ft_cmpexact(node->args[node->args_index], \
								"echo"))
							{
								str = ft_strjoin(inter[j], " ");
								args = expantion(str, args);
								free(str);
							}
							else
								args = expantion(inter[j], args);
							j++;
						}
					}
					else if (j == 1)
						args = expantion(inter[0], args);
					clear_arr_of_strs(inter);
				}
			}
			else
			{
				str = node->args[i];
				args = expantion(str, args);
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
		detect_in_redirection(node, tty);
		detect_out_redirection(node);
	}
}

void	postexecute(t_ast_node *node)
{
	char	*file;

	multiple_output_redirections(node);
	file = tmp_path(node->nid, REDIRECT_IN);
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
