/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:49:26 by jflores           #+#    #+#             */
/*   Updated: 2025/02/23 15:48:34 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	parse_command_inner(char **inter, char ***args)
{
	int		j;

	j = 0;
	while (inter[j])
	{
		*args = expantion(inter[j], *args);
		j++;
	}
}

void	parse_command_master_inner(char *str, char ***args)
{
	int		j;
	char	**inter;

	inter = ft_split(str, ' ');
	if (inter)
	{
		j = 0;
		while (inter[j])
			j++;
		if (j > 1)
			parse_command_inner(inter, args);
		else if (j == 1)
			*args = expantion(inter[0], *args);
		clear_arr_of_strs(inter);
	}
}

void	parse_command_master(t_ast_node *node, int i, char ***args, \
	t_terminal *tty)
{
	char	*str;

	str = interpolation(node->args[i], i, tty);
	if (str)
	{
		if (ft_cmpexact("echo", node->args[0]))
			*args = expantion(str, *args);
		else
			parse_command_master_inner(str, args);
		free(str);
	}
}
