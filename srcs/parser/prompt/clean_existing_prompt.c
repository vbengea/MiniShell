/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_existing_prompt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:48:09 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:11:33 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	clean_existing_prompt(t_terminal *tty)
{
	if (tty->prompt)
	{
		free(tty->prompt);
		tty->prompt = NULL;
	}
}
