/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colored_cwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:44:45 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 19:05:29 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

char	*get_colored_cwd(void)
{
	char	*cwd;
	char	*colored_cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	colored_cwd = ft_strjoin(BLUE, cwd);
	free(cwd);
	return (colored_cwd);
}
