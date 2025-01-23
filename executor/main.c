/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/23 09:46:48 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

int	main(int argc, char **argv, char **env)
{
	t_node	*s;
	int		fd[2];

	(void) argc;
	(void) argv;
	s = get_stree2();
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	process(s, env, fd);
	free(s);
	return (0);
}
