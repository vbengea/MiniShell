/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:59 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/13 20:38:34 by jflores          ###   ########.fr       */
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

typedef struct s_terminal t_terminal;

typedef struct s_history
{
	char	*commands[MAX_HISTORY_LINES];
	int		count;
}	t_history;


char	*get_history_filepath(t_terminal *tty);
void	load_history_from_file(t_history *myhist, t_terminal *tty);
void	save_history_to_file(t_history *myhist, t_terminal *tty);
void	init_local_history(t_history *myhist);
void	add_to_both_histories(t_history *myhist, const char *line);

#endif