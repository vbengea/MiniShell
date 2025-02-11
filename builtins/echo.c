/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/11 18:38:34 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void	new_line(t_ast_node *node)
{
	if (node->out_fd < 0)
		printf("\n");
	else
		ft_putchar_fd('\n', node->out_fd);
}

void	echo_bi(t_ast_node *node)
{
	int		i;
	char	*str;
	char	**params;
	int		is_n_option;

	is_n_option = true;
	params = node->args;
	i = 1;
	if (ft_strlen(params[i]) == 2 && params[i][0] == '-' && params[i][1] == 'n')
	{
		is_n_option = false;
		i++;
	}
	while (params[i])
	{
		str = params[i];
		if (node->out_fd < 0)
		{
			printf("%s", str);
			if (params[i + 1] && node->has_space[i])
				printf(" ");
		}
		else
		{
			ft_putstr_fd(str, node->out_fd);
			if (params[i + 1] && node->has_space[i])
				ft_putstr_fd(" ", node->out_fd);
		}
		i++;
	}
	if (is_n_option)
		new_line(node);
}
