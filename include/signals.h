/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:32 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/13 18:43:15 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H

# define SIGNALS_H

# include <signal.h>

void	set_tty(t_terminal *tty);
void	setup_signal_handlers(void);
void	setup_signal_handlers_process(void);
void	setup_signal_handlers_child(void);
void	handle_sigquit(int signal);
void	handle_sigint(int signal);
void	handle_sigexec(int signal);
void	cpshell(t_terminal *tty);

#endif
