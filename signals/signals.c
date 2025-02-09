/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/07 21:51:28 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	set_tty(void)
{
	struct termios t;

	tcgetattr(0, &t);
	tcsetattr(0, 0, &t );
	// t.c_lflag &= ~ECHOCTL;
	// tcsetattr(0, 0, &t);
	setup_signal_handlers();
}

void	handle_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line(" ", 0);
	rl_redisplay();
}

void	handle_sigquit(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	setup_signal_handlers();
}

void	setup_signal_handlers(void)
{
	struct	sigaction sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}


void	setup_signal_handlers_process(void)
{
	struct	sigaction sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigquit;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}