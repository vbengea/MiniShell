/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
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
	tcgetattr(0, &t);
	tcsetattr(0, 0, &t);
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

void	handle_sigexec(int signal)
{
	(void)signal;
	exit(0);
}

void	handle_sigquit(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	rl_redisplay();
	setup_signal_handlers();
	printf("\n");
}

void	handle_sigpipe(int signal)
{
	(void) signal;
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_signal_handlers_process(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigquit;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigpipe;
	sigaction(SIGCHLD, &sa, NULL);
}

void	setup_signal_handlers_child(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigexec;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}
