/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:32 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/06 20:39:31 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H

# define SIGNALS_H

# include <signal.h>

void	set_tty(char ***env);
void	setup_signal_handlers(void);
void	setup_signal_handlers_process(void);
void	handle_sigquit(int signal);
void	handle_sigint(int signal);
void	cpshell(char ***env);

#endif
