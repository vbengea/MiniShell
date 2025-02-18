/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:32 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/18 19:29:09 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H

# define TERMINAL_H

# include "headers.h"

void	set_tty(t_terminal *tty);
void	setup_signal_handlers(void);
void	handle_sigint(int signal);
void	check_shlvl(t_terminal *tty);
void	build_terminal(char **env, t_terminal	*tty);
void	loop_terminal(t_terminal *tty);
void	destroy_terminal(t_terminal *tty);
void	tty_init(char **env, t_terminal *tty);
void	loop_inner(char *input, t_token *tokens, t_terminal *tty);
void	execute_ast(t_terminal *tty);
void	exec_one(char *input, t_terminal *tty);

#endif
