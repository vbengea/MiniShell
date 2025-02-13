/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:32 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/13 13:37:05 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H

# define SIGNALS_H

# include <signal.h>

void	set_tty(t_terminal *tty);
void	setup_signal_handlers(void);
void	setup_signal_handlers_process(void);
void	handle_sigquit(int signal);
void	handle_sigint(int signal);
void	cpshell(t_terminal *tty);

#endif
