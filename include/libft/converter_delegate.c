/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_delegate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:25:35 by juandanielf       #+#    #+#             */
/*   Updated: 2024/10/30 09:31:10 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	convert_char(t_spec *sp)
{
	char	ch;

	ch = va_arg(*(sp->lst), int);
	sp->str = ft_calloc(1 + 1, 1);
	if (sp->str)
	{
		if (sp->width)
			sp->width--;
		sp->count++;
		sp->ch = ch;
	}
}

void	convert_str(t_spec *sp, char *str)
{
	str = va_arg(*(sp->lst), char *);
	if (str)
		sp->str = ft_strdup(str);
	if (!sp->str)
	{
		sp->str = malloc(6 + 1);
		ft_strlcpy(sp->str, "(null)", 6 + 1);
	}
}

void	convert_unsigned(unsigned long n, char const *base, t_spec *sp)
{
	int		i;

	numeric_stats(n, sp);
	if (n < 9)
		i = 1;
	else
		i = digits_count_base(n, base);
	sp->str = ft_calloc(i + 1, 1);
	if (sp->str)
	{
		set_str_base(sp->str, n, i, base);
		if (n == 0)
			sp->str[0] = '0';
	}
}

void	convert_hex(unsigned long n, int is_up, t_spec *sp)
{
	if (!n && sp->conversion == 'p')
	{
		sp->str = malloc(5 + 1);
		if (sp->str)
			ft_strlcpy(sp->str, "(nil)", 5 + 1);
	}
	else
	{
		if (is_up)
			convert_unsigned(n, "0123456789ABCDEF", sp);
		else
			convert_unsigned(n, "0123456789abcdef", sp);
	}
}

void	convert_integer(int n, t_spec *sp)
{
	numeric_stats(n, sp);
	if (n < 0)
	{
		if (n == -2147483648)
		{
			sp->str = max_negative_to_positive();
			return ;
		}
		else
			n *= -1;
	}
	sp->str = ft_itoa(n);
}
