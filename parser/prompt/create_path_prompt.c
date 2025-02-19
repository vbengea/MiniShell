/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:46:57 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 18:47:18 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

char	*create_path_prompt(char *base_prompt)
{
	char *initial_prompt;
	char *colored_cwd;
	char *combined_prompt;
	char *final;

	initial_prompt = create_initial_prompt(base_prompt);
	if (!initial_prompt)
		return (NULL);
	colored_cwd = get_colored_cwd();
	if (!colored_cwd)
	{
		free(initial_prompt);
		return (NULL);
	}
	combined_prompt = ft_strjoin(initial_prompt, colored_cwd);
	free(initial_prompt);
	free(colored_cwd);
	if (!combined_prompt)
		return (NULL);
	final = append_prompt_suffix(combined_prompt);
	free(combined_prompt);
	return (final);
}
