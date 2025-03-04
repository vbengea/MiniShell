/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_user_host_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:42:20 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:11:47 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

char	*create_user_host_prompt(char *user, char *host)
{
	char	*partial_prompt;
	char	*color_prompt;
	char	*final_prompt;

	partial_prompt = ft_strjoin(user, "@");
	if (!partial_prompt)
		return (NULL);
	color_prompt = ft_strjoin(GREEN, partial_prompt);
	free(partial_prompt);
	if (!color_prompt)
		return (NULL);
	partial_prompt = ft_strjoin(color_prompt, host);
	free(color_prompt);
	if (!partial_prompt)
		return (NULL);
	final_prompt = ft_strjoin(partial_prompt, GREEN);
	free(partial_prompt);
	return (final_prompt);
}
