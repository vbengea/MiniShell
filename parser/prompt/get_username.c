/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_username.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:41:41 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 18:42:10 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

char	*get_username(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		user = ft_strdup("minishell");
	else
		user = ft_strdup(user);
	return (user);
}
