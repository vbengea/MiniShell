/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:46:50 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/23 11:54:08 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 12))
		return (true);
	return (false);
}

bool	ft_isquote(char c)
{
	if (c == 34 || c == 39)
		return (true);
	return (false);
}
