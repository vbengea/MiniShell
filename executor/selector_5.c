/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:49:26 by jflores           #+#    #+#             */
/*   Updated: 2025/02/19 21:36:30 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	parse_command_inner(char **inter, t_ast_node *node, char ***args)
{
	char	*str;
	int		j;

	j = 0;
	while (inter[j])
	{
		if (ft_cmpexact(node->args[node->args_index], "echo"))
		{
			str = ft_strjoin(inter[j], " ");
			*args = expantion(str, *args);
			free(str);
		}
		else
			*args = expantion(inter[j], *args);
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
			*args = expantion(inter[0], *args);
		clear_arr_of_strs(inter);
	}
}
