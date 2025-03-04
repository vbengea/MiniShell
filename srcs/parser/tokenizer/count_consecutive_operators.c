/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_consecutive_operators.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:32:38 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:12:34 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	count_consecutive_operators(const char *input, int *i, char op)
{
	int	count;

	count = 0;
	while (input[*i] == op)
	{
		count++;
		(*i)++;
	}
	return (count);
}
