/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/24 20:52:55 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

int	main(int argc, char **argv, char **env)
{
	t_ast_node	*s;
	int			fd[2];

	(void) argc;
	(void) argv;
	s = get_data_structure_2();
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	binary(s, env, fd);
	free(s);
	return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_node	*s;
// 	int		fd[2];

// 	(void) argc;
// 	(void) argv;
// 	s = get_stree3();
// 	fd[0] = STDIN_FILENO;
// 	fd[1] = STDOUT_FILENO;
// 	process(s, env, fd);
// 	free(s);
// 	return (0);
// }
