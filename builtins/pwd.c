/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/12 18:59:18 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	pwd_bi(t_ast_node *node)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL && !node->args[1])
	{
		if (node->out_fd < 0)
			printf("%s\n", cwd);
		else
			ft_putstrnl_fd(cwd, node->out_fd);
	}
	else
	{
		if (node->out_fd < 0)
			printf("Invalid syntax\n");
		else
			ft_putstrnl_fd("Invalid syntax\n", node->out_fd);
	}
}




