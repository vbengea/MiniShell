/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:59 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/13 20:20:03 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# ifndef HISTORY_FILE
#  define HISTORY_FILE "/.minishell_history"
# endif

# ifndef MAX_HISTORY_LINES
#  define MAX_HISTORY_LINES 500
# endif

typedef struct s_history
{
	char	*commands[MAX_HISTORY_LINES];
	int		count;
}	t_history;


char	*get_history_filepath(char **env);
void	load_history_from_file(char **env, t_history *myhist);
void	save_history_to_file(char **env, t_history *myhist);
void	init_local_history(t_history *myhist);
void	add_to_both_histories(t_history *myhist, const char *line);

#endif