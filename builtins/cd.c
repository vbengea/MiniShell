/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/25 16:37:00 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

int		cd(const char *path, char **env)
{
	int		r;
	int		i;
	int		len;
	char	*str;
	
	if (path == NULL)
		path = getenv("HOME");
	r = chdir(path);
	if (r != 0)
		perror("cd builtin failed");
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			//free(env[i]);
			str = ft_strjoin("PWD=", path);
			len = ft_strlen(str);
			env[i] = malloc(len + 1);
			ft_strlcpy(env[i], str, len + 1);
			env[i][len] = '\0';
		}
		i++;
	}
	return (r);
}
