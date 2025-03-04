/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:58:32 by juandanielf       #+#    #+#             */
/*   Updated: 2024/09/24 11:03:49 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	digit_count(int n)
{
	int	d;

	d = 0;
	while (n > 0)
	{
		n /= 10;
		d++;
	}
	return (d);
}

static	size_t	exponent(size_t digits)
{
	size_t	m;

	m = 1;
	while (digits > 0)
	{
		m *= 10;
		digits--;
	}
	return (m);
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	m;
	size_t	ex;
	size_t	digits;

	m = 0;
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	else if (n == 0)
		ft_putchar_fd('0', fd);
	digits = digit_count(n);
	while (digits--)
	{
		ex = exponent(digits);
		m = n / ex;
		ft_putchar_fd(m + '0', fd);
		n -= (m * ex);
	}
}
