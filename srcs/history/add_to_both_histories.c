/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_both_histories.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:49:11 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:08:23 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	add_to_both_histories(t_history *myhist, const char *line)
{
	int	i;

	add_history(line);
	if (myhist->count < MAX_HISTORY_LINES)
	{
		myhist->commands[myhist->count] = ft_strdup(line);
		if (!myhist->commands[myhist->count])
			return ;
		myhist->count++;
	}
	else
	{
		free(myhist->commands[0]);
		i = 1;
		while (i < MAX_HISTORY_LINES)
		{
			myhist->commands[i - 1] = myhist->commands[i];
			i++;
		}
		myhist->commands[MAX_HISTORY_LINES - 1] = ft_strdup(line);
		if (!myhist->commands[MAX_HISTORY_LINES - 1])
			return ;
	}
}
