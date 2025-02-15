/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:36:15 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/15 21:11:38 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"

bool	handle_env_var_token(bool prev_export, int *count)
{
	if (!prev_export)
		(*count)++;
	*count += 2;
	return (true);
}
