/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_local_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:48:46 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 11:54:37 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

t_history	*init_local_history(void)
{
	t_history	*myhist;
	int			i;

	myhist = malloc(sizeof(t_history));
	if (!myhist)
		return (NULL);
	ft_memset(myhist, 0, sizeof(t_history));
	myhist->count = 0;
	i = 0;
	while (i < MAX_HISTORY_LINES)
	{
		myhist->commands[i] = NULL;
		i++;
	}
	return (myhist);
}
