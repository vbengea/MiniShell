/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:25:59 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/10 20:09:09 by vbengea          ###   ########.fr       */
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

char	*get_history_filepath(char **env);
void	load_history_from_file(char **env);
void	save_history_to_file(char **env);

#endif