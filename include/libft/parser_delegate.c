/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_delegate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:27:33 by jflores           #+#    #+#             */
/*   Updated: 2024/10/30 09:30:32 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	do_asterisk(t_spec *sp)
{
	int	i;

	sp->flag_asterisk += 1;
	i = va_arg(*(sp->lst), int);
	if (i < 0)
	{
		i *= -1;
		if (sp->is_precision_dot)
		{
			sp->precision = -1;
			sp->is_precision_dot = 0;
			return ;
		}
		else
			sp->flag_minus = 1;
	}
	if (sp->is_precision_dot)
		sp->precision = i;
	else
		sp->width = i;
}

void	set_flag(char c, t_spec *sp)
{
	if (c == sp->flags[0])
		sp->flag_pound += 1;
	else if (c == sp->flags[1])
		sp->flag_zero += 1;
	else if (c == sp->flags[2])
		sp->flag_minus += 1;
	else if (c == sp->flags[3])
		sp->flag_space += 1;
	else if (c == sp->flags[4])
		sp->flag_plus += 1;
	else if (c == sp->flags[5])
		do_asterisk(sp);
}
