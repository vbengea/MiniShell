/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:10:31 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/02 11:38:18 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

bool	is_operator(char c)
{
	return (c == '|'
		|| c == '<'
		|| c == '>'
		|| c == '&'
		|| c == ';'
		|| c == '('
		|| c == ')'
		|| (c >= '0' && c <= '9')); // Recognize file descriptors redirections
}
