/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:59 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/18 19:37:52 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "headers.h"
# include "data_structure.h"

# ifndef HISTORY_FILE
#  define HISTORY_FILE "/.minishell_history"
# endif

# ifndef MAX_HISTORY_LINES
#  define MAX_HISTORY_LINES 500
# endif

typedef struct s_history	t_history;
typedef struct s_terminal	t_terminal;

char	*get_history_filepath(t_terminal *tty);
void	load_history_from_file(t_history *myhist, t_terminal *tty);
void	save_history_to_file(t_history *myhist, t_terminal *tty);
t_history	*init_local_history(void);
void	add_to_both_histories(t_history *myhist, const char *line);

#endif