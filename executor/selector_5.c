/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:49:26 by jflores           #+#    #+#             */
/*   Updated: 2025/02/23 14:04:59 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	parse_command_inner(char **inter, t_ast_node *node, char ***args)
{
	int		j;

	j = 0;
	(void) node;
 	while (inter[j])
	{
		*args = expantion(inter[j], *args, node);
		j++;
	}
}

void	parse_command_master(t_ast_node *node, int i, char ***args, \
	t_terminal *tty)
{
	int		j;
	char	*str;
	char	**inter;

	str = interpolation(node->args[i], i, tty);
	if (ft_cmpexact("echo", node->args[0]))
		*args = expantion(str, *args, node);
	else
	{
		inter = ft_split(str, ' ');
		free(str);
		if (inter)
		{
			j = 0;
			while (inter[j])
				j++;
			if (j > 1)
				parse_command_inner(inter, node, args);
			else if (j == 1)
				*args = expantion(inter[0], *args, node);
			clear_arr_of_strs(inter);
		}
	}
}
