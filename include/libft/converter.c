/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:40:14 by jflores           #+#    #+#             */
/*   Updated: 2024/10/30 09:30:58 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	base_str(t_spec *sp)
{
	if (sp->conversion == 'p')
		sp->flag_pound = 1;
	if (sp->conversion == 'c')
		convert_char(sp);
	else if (sp->conversion == 's')
		convert_str(sp, NULL);
	else if (sp->conversion == 'p')
		convert_hex(va_arg(*(sp->lst), unsigned long), 0, sp);
	else if (sp->conversion == 'd' || sp->conversion == 'i')
		convert_integer(va_arg(*(sp->lst), int), sp);
	else if (sp->conversion == 'u')
		convert_unsigned(va_arg(*(sp->lst), unsigned int), \
			"0123456789", sp);
	else if (sp->conversion == 'x' || sp->conversion == 'X')
		convert_hex(va_arg(*(sp->lst), unsigned int), \
			sp->conversion == 'X', sp);
	else if (sp->conversion == '%')
	{
		sp->str = malloc(1 + 1);
		if (sp->str)
		{
			sp->str[0] = '%';
			sp->str[1] = '\0';
		}
	}
}

void	numeric_stats(long double n, t_spec *sp)
{
	sp->is_numeric = 1;
	if (sp->conversion == 'i' || sp->conversion == 'd')
		sp->is_signed = 1;
	if (n < 0 && sp->is_signed)
		sp->is_positive = 0;
}

void	set_str_base(char *str, unsigned long n, int i, \
	char const *base)
{
	int	m;
	int	b;

	m = 0;
	b = ft_strlen(base);
	str[i] = '\0';
	if (n == 0)
		str[0] = '0';
	else
	{
		while (n > 0)
		{
			m = n % b;
			n /= b;
			*(str + --i) = base[m];
		}
	}
}

int	digits_count_base(unsigned long n, char const *base)
{
	int	i;
	int	b;

	i = 0;
	b = ft_strlen(base);
	while (n > 0)
	{
		i++;
		n /= b;
	}
	return (i);
}

int	convert_specifier(t_spec *sp, int i)
{
	base_str(sp);
	if (sp->str)
	{
		pad_str(sp);
		if (sp->str)
		{
			sp->count += ft_strlen(sp->str);
			if (sp->conversion == 'c')
			{
				if (sp->flag_minus)
				{
					write(1, &sp->ch, 1);
					ft_putstr_fd(sp->str, 1);
				}
				else
				{
					ft_putstr_fd(sp->str, 1);
					write(1, &sp->ch, 1);
				}
			}
			else
				ft_putstr_fd(sp->str, 1);
		}
	}
	return (i);
}
