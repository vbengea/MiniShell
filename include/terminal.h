/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:32 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/16 11:42:49 by jflores          ###   ########.fr       */
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

#endif
