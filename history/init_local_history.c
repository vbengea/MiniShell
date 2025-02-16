/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_local_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:48:46 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/16 18:49:01 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	init_local_history(t_history *myhist)
{
	int	i;

	myhist->count = 0;
	i = 0;
	while (i < MAX_HISTORY_LINES)
	{
		myhist->commands[i] = NULL;
		i++;
	}
}
