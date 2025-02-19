/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_prompt_suffix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:45:36 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 18:45:55 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

char *append_prompt_suffix(char *prompt)
{
	char *final;

	final = ft_strjoin(prompt, WHITE "€ " RESET);
	return (final);
}
