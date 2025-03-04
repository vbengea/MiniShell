/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:36:15 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:10:24 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

bool	handle_env_var_token(bool prev_export, int *count)
{
	if (!prev_export)
		(*count)++;
	*count += 2;
	return (false);
}
