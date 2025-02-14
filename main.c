/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/15 00:24:50 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/headers.h"

int	main(int argc, char **argv, char **env)
{
	t_terminal	tty;

	(void) argv;
	if (argc != 1)
	{
		printf("Incorrect number of arguments.\n");
		exit(1);
	}
	build_terminal(env, &tty);
	loop_terminal(&tty);
	destroy_terminal(&tty);
	return (0);
}
