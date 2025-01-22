/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:13:16 by jflores           #+#    #+#             */
/*   Updated: 2024/10/30 09:30:35 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	parse_flags(char *str, t_spec *sp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (sp->flags[i])
	{
		if (str[j] == sp->flags[i])
		{
			set_flag(str[j], sp);
			j++;
			i = 0;
			continue ;
		}
		i++;
	}
	return (j);
}

static	int	parse_numeric(char *str, t_spec *sp, char is_precision)
{
	size_t	i;
	int		n;

	i = 0;
	n = 0;
	if (is_precision)
		sp->precision = 0;
	while (ft_isdigit(str[i]))
		n = n * 10 + (str[i++] - '0');
	if (n > 0)
	{
		if (is_precision)
			sp->precision = n;
		else
			sp->width = n;
	}
	return (i);
}

static	int	parse_conversion(char *str, t_spec *sp)
{
	size_t	i;

	i = 0;
	while (sp->conversions[i])
	{
		if (str[0] == sp->conversions[i])
		{
			sp->conversion = str[0];
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse_token(char *str, t_spec *sp)
{
	int	i;

	i = 0;
	i += parse_flags((str + i), sp);
	i += parse_numeric((str + i), sp, 0);
	if (*(str + i) == '.')
	{
		sp->is_precision_dot = 1;
		i += 1;
		i += parse_numeric((str + i), sp, 1);
	}
	i += parse_flags((str + i), sp);
	i += parse_conversion((str + i), sp);
	if (sp->conversion)
	{
		i = convert_specifier(sp, i);
		if (sp->str)
			free(sp->str);
	}
	else
		i = 0;
	return (i);
}
