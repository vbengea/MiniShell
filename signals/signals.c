/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/04 11:22:18 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

int	SIGNAL = -1;

static	void	ctr_handler(int signal)
{
	if (signal == SIGUSR1)
		SIGNAL = 1;
	else if (signal == SIGUSR2)
		SIGNAL = -1;
	else if (signal == SIGINT)
	{
		if (SIGNAL == -1)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			SIGNAL = -1;
	}
}

static	void	intercepting_signals(void)
{
	struct	sigaction	cfg_sigint;
	struct	sigaction	cfg_sigquit;
	struct	sigaction	cfg_sigusr1;
	struct	sigaction	cfg_sigusr2;

	ft_bzero(&cfg_sigint, sizeof(cfg_sigint));
	ft_bzero(&cfg_sigquit, sizeof(cfg_sigquit));
	ft_bzero(&cfg_sigusr1, sizeof(cfg_sigusr1));
	ft_bzero(&cfg_sigusr2, sizeof(cfg_sigusr2));

	cfg_sigint.sa_handler = &ctr_handler;
	cfg_sigquit.sa_handler = SIG_IGN;
	cfg_sigusr1.sa_handler = &ctr_handler;
	cfg_sigusr2.sa_handler = &ctr_handler;

	sigaction(SIGINT, &cfg_sigint, NULL);
	sigaction(SIGQUIT, &cfg_sigquit, NULL);
	sigaction(SIGUSR1, &cfg_sigusr1, NULL);
	sigaction(SIGUSR2, &cfg_sigusr2, NULL);
}

void	set_tty(void)
{
	struct termios t;
	char		*path;

	path = getenv("PATH");
	path = ft_strjoin(path, ":.");
	setenv("PATH", path, 1);
	tcgetattr(0, &t);
	tcsetattr(0, 0, &t );
	// t.c_lflag &= ~ECHOCTL;
	// tcsetattr(0, 0, &t);
	intercepting_signals();
}
