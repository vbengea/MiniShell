/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:57:15 by jflores           #+#    #+#             */
/*   Updated: 2025/02/16 19:00:53 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	tty_init(char **env, t_terminal *tty)
{
	if (tty)
	{
		tty->files[0] = STDIN_FILENO;
		tty->files[1] = STDOUT_FILENO;
		tty->files[2] = 0;
		tty->ast = NULL;
		tty->env = copy_arr_of_strs(env, 0, 0);
		tty->env_local = malloc(sizeof(char *) * 1);
		tty->env_cmd = malloc(sizeof(char *) * 1);
		tty->env_local[0] = NULL;
		tty->env_cmd[0] = NULL;
    }
}
