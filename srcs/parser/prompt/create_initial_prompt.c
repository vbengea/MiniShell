/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_initial_prompt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:43:31 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:11:40 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

char	*create_initial_prompt(char *base_prompt)
{
	char	*partial_prompt;

	partial_prompt = ft_strjoin(base_prompt, WHITE ":");
	return (partial_prompt);
}
