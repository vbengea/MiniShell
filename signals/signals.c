/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/09 23:31:38 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

int	SIGNAL;

void	cpshell(char ***env)
{
	char			**args;
	char			*cmd;
	char			*tmp;
	t_ast_node		*node;

	cmd = getenv("HOME");
	cmd = ft_strjoin(cmd, "/.local/bin/minishell");
	if (cmd && access(cmd, F_OK | X_OK) != 0)
	{
		tmp = cmd;
		cmd = ft_strjoin("cp minishell ", cmd);
		free(tmp);
		args = ft_split(cmd, ' ');
		node = create_ast_node(NODE_CMND, args);
		selector(node, env, NULL);
		free(cmd);
		free_redirect_ast(node, 0);
	}
}

void	set_tty(char ***env)
{
	struct termios 	t;

	cpshell(env);
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

void	handle_sigpipe(int signal)
{
	(void)signal;
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
	sa.sa_handler = handle_sigpipe;
	sigaction(SIGCHLD, &sa, NULL);
}
