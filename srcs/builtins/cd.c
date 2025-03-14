/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/03/04 19:06:07 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	cd_bi(t_ast_node *node, t_terminal *tty)
{
	int		r;
	char	cwd[PATH_MAX];
	char	*path;

	r = 1;
	if (node->args[1] && node->args[2])
		return (printf("VJ.SH: cd: too many arguments\n"), -1);
	path = node->args[1];
	if (path == NULL)
		path = get_env(node, -1, "HOME", tty);
	if (path)
	{
		r = chdir(path);
		if (r != 0)
			perror("VJ.SH: cd");
		else
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
				set_env(node, "PWD", cwd, tty);
		}
		if (node->args[1] == NULL)
			free(path);
	}
	return (r);
}
