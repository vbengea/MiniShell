/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history_filepath.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:48:16 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:08:27 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

char	*get_history_filepath(t_terminal *tty)
{
	char	*home;
	char	*tmp;

	home = get_env(NULL, -1, "HOME", tty);
	if (!home)
		return (NULL);
	tmp = home;
	home = ft_strjoin(home, HISTORY_FILE);
	free(tmp);
	return (home);
}
