/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/18 19:42:25 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/headers.h"

int	main(int argc, char **argv, char **env)
{
	t_terminal	tty;

	if (argc == 1)
	{
		build_terminal(env, &tty);
		loop_terminal(&tty);
		destroy_terminal(&tty);
	}
	else if (argc >= 3 && ft_cmpexact(argv[1], "-c"))
	{
		build_terminal(env, &tty);
		exec_one(argv[2], &tty);
		destroy_terminal(&tty);
	}
	else
	{
		printf("minishell: %s: No such file or directory\n", argv[1]);
		exit(1);
	}

	return (0);
}
