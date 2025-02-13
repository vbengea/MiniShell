/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:59 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/13 18:16:11 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "headers.h"

# ifndef HISTORY_FILE
#  define HISTORY_FILE "/.minishell_history"
# endif

# ifndef MAX_HISTORY_LINES
#  define MAX_HISTORY_LINES 500
# endif

char	*get_history_filepath(t_terminal *tty);
void	load_history_from_file(t_terminal *tty);
void	save_history_to_file(t_terminal *tty);

#endif