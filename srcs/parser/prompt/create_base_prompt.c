/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_base_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:50:30 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:11:36 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

char	*create_base_prompt(char *user, char *host)
{
	char	*user_host_prompt;

	user_host_prompt = create_user_host_prompt(user, host);
	free(user);
	free(host);
	return (user_host_prompt);
}
