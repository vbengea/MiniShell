/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/25 16:37:00 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	**export_bi(const char *key, const char *value, char **env)
{
	(void) key;
	(void) value;
	(void) env;
	char	*str;
	int		len;

	(void) str;
	(void) len;
	len = ft_strlen(key) + 1 + ft_strlen(value) + 1;
	str = malloc(len + 1);
	ft_strlcat(str, key, len);
	ft_strlcat(str, "=", len);
	ft_strlcat(str, value, len);
	env = add_arr_of_strs(env, str);
	free(str);
	return (env);
}