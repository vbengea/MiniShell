/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juandanielflores <juandanielflores@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:24:26 by juandanielf       #+#    #+#             */
/*   Updated: 2024/09/22 02:59:37 by juandanielf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_digits(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static	void	toa(char *str, int n, int i)
{
	int	m;

	m = 0;
	while (n > 0)
	{
		m = n % 10;
		n /= 10;
		*(str + i--) = m + '0';
	}
}

static	void	set_str(char *str, int n, int i, int sign)
{
	int	j;

	j = 0;
	if (sign)
		str[j++] = '-';
	if (n == 0)
		str[0] = '0';
	else
		toa((str + j), n, i - 1 - j);
	str[i] = '\0';
}

static char	*set_max_negative(void)
{
	char	*str;

	str = malloc(12);
	if (str)
		ft_strlcpy(str, "-2147483648", 12);
	return (str);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		i;
	char	*str;

	sign = 0;
	i = 0;
	if (n < 0)
	{
		if (n == -2147483648)
			return (set_max_negative());
		sign = 1;
		n *= -1;
		i++;
	}
	if (n == 0)
		i = 1;
	else
		i += count_digits(n);
	str = malloc(i + 1);
	if (str)
		set_str(str, n, i, sign);
	return (str);
}
