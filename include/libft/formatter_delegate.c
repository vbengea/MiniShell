/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatter_delegate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:59:18 by jflores           #+#    #+#             */
/*   Updated: 2024/10/30 09:31:01 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_zero(char *s)
{
	if (ft_strlen(s) == 1 && *s == '0')
		return (1);
	else
		return (0);
}

char	get_pad(t_spec *sp)
{
	if (sp->flag_zero && sp->precision == -1 && !sp->is_precision_dot && \
		!sp->flag_minus && ft_strchr("diuxX", sp->conversion))
		return ('0');
	return (' ');
}

void	prepad(t_spec *sp, char *chopped)
{
	if (!ft_strnstr(chopped, "(nil)", 5) && !ft_strnstr(chopped, "(null)", 6))
	{
		if (ft_strchr("pxX", sp->conversion) && \
			sp->flag_pound && !is_zero(chopped))
		{
			chopped[0] = '0';
			chopped[1] = 'x';
			if (sp->conversion == 'X')
				chopped[1] = 'X';
		}
		if (ft_strchr("di", sp->conversion) && (!sp->is_positive || \
			sp->flag_space || sp->flag_plus))
		{
			if (!sp->is_positive)
				chopped[0] = '-';
			if (sp->is_positive && sp->flag_space)
				chopped[0] = ' ';
			if (sp->is_positive && sp->flag_plus)
				chopped[0] = '+';
		}
	}
}

int	allow_precision(t_spec *sp, int len)
{
	if ((sp->is_precision_dot && sp->precision >= len) || \
		(sp->precision == -1 && !sp->is_precision_dot))
	{
		return (1);
	}
	return (0);
}

int	validate(t_spec *sp)
{
	if (sp->str)
	{
		if (sp->conversion == '%')
			return (0);
		else if (sp->conversion == 's' && \
			sp->precision != -1 && \
			sp->precision < (int)ft_strlen(sp->str) && \
			ft_strnstr(sp->str, "(null)", 6))
		{
			sp->str[0] = '\0';
			sp->str[1] = '\0';
		}
		return (1);
	}
	return (0);
}
