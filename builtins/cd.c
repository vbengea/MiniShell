/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/14 00:05:51 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

int	cd_bi(t_ast_node *node, t_terminal *tty)
{
	int		r;
	char	cwd[PATH_MAX];
	char	*path;

	if (node->args[2])
		return (printf("VJ.SH: cd: too many arguments\n"), -1);
	path = node->args[1];
	if (path == NULL)
		path = get_env(node, "HOME", tty);
	r = chdir(path);
	if (r != 0)
		perror("VJ.SH: cd");
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			set_env(node, "PWD", cwd, tty);
	}
	return (r);
}
