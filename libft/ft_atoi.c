/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 02:01:12 by juandanielf       #+#    #+#             */
/*   Updated: 2024/09/21 20:40:24 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_whitespace(char ch)
{
	if ((ch >= 9 && ch <= 13) || (ch == 32))
		return (1);
	else
		return (0);
}

static int	is_sign(char ch)
{
	return (ch == '+' || ch == '-');
}

static	int	get_number(const char *str, int sign)
{
	int	i;
	int	processing;

	i = 0;
	processing = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			processing = 1;
			if (i == 0)
				i = *str - '0';
			else
				i = i * 10 + (*str - '0');
		}
		else
		{
			if (processing)
				break ;
			else
				return (0);
		}
		str++;
	}
	return (i * sign);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		neg;

	sign = 0;
	neg = 1;
	while (*str)
	{
		if (is_whitespace(*str))
		{
			if (sign)
				return (0);
		}
		else if (is_sign(*str))
		{
			if (sign)
				return (0);
			sign = 1;
			if (*str == '-')
				neg = -1;
		}
		else
			return (get_number(str, neg));
		str++;
	}
	return (0);
}
