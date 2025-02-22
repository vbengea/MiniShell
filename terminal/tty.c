/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                  	                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/16 11:30:06 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	check_shlvl(t_terminal *tty)
{
	int		l;
	char	*lvl;

	lvl = getenv("SHLVL");
	if (lvl)
	{
		l = ft_atoi(lvl) + 1;
		lvl = ft_itoa(l);
	}
	else
		lvl = ft_strdup("1");
	set_env(NULL, "SHLVL", lvl, tty);
	free(lvl);
}

void	set_tty(t_terminal *tty)
{
	struct termios	t;

	check_shlvl(tty);
	set_env(NULL, "?", "0", tty);
	tcgetattr(0, &t);
	tcsetattr(0, 0, &t);
	setup_signal_handlers();
}
