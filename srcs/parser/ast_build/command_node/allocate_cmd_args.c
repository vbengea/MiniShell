/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_cmd_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:34:46 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:10:01 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

char	**allocate_cmd_args(int count)
{
	char	**cmd_args;

	cmd_args = malloc(sizeof(char *) * (count + 1));
	if (!cmd_args)
		return (NULL);
	return (cmd_args);
}
