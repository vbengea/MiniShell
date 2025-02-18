/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/18 20:03:26 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/headers.h"

int	main(int argc, char **argv, char **env)
{
	t_terminal	tty;

	if (argc == 1)
	{
		build_terminal(env, &tty, 1);
		loop_terminal(&tty);
		destroy_terminal(&tty);
	}
	else if (argc >= 3 && ft_cmpexact(argv[1], "-c"))
	{
		build_terminal(env, &tty, 0);
		exec_one(argv[2], &tty);
		clear_arr_of_strs(tty.env);
		clear_arr_of_strs(tty.env_local);
		clear_arr_of_strs(tty.env_cmd);
	}
	else
	{
		printf("minishell: %s: No such file or directory\n", argv[1]);
		exit(1);
	}

	return (0);
}
