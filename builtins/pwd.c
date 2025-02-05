/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/25 16:37:00 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	pwd_bi(t_ast_node *node)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (node->fd < 0)
			printf("%s\n", cwd);
		else
		{
			ft_putstrnl_fd(cwd, node->fd);
		}
	}
}
