/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/11 18:36:51 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

int	cd_bi(t_ast_node *node, char ***env)
{
	int		r;
	char	cwd[PATH_MAX];
	char	*path;

	path = node->args[1];
	if (path == NULL)
		path = get_env("HOME", *env);
	r = chdir(path);
	if (r != 0)
		perror("cd builtin failed");
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			*env = set_env("PWD", cwd, *env);
	}
	return (r);
}
