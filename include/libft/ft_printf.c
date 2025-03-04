/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:06:18 by jflores           #+#    #+#             */
/*   Updated: 2024/10/30 09:27:35 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	init_spec(t_spec *sp, va_list *lst)
{
	sp->lst = lst;
	sp->conversion = '\0';
	sp->width = 0;
	sp->precision = -1;
	sp->is_precision_dot = 0;
	ft_strlcpy(sp->flags, "#0- +*", 7);
	sp->flag_pound = 0;
	sp->flag_zero = 0;
	sp->flag_minus = 0;
	sp->flag_space = 0;
	sp->flag_plus = 0;
	sp->flag_asterisk = 0;
	sp->is_numeric = 0;
	sp->is_positive = 1;
	sp->is_signed = 0;
	ft_strlcpy(sp->conversions, "cspdiuxX%", 10);
	sp->str = NULL;
	sp->base = NULL;
	sp->sign = '\0';
}

char	*max_negative_to_positive(void)
{
	char	*str;

	str = ft_calloc(11 + 1, 1);
	if (str)
		ft_strlcpy(str, "2147483648", 11);
	return (str);
}

static	void	iter(t_spec	*sp, va_list *lst, char *str)
{
	int	i;

	while (*str)
	{
		if (*str == '%')
		{
			init_spec(sp, lst);
			i = parse_token((str + 1), sp);
			if (i == -1)
				break ;
			else if (i != 0)
			{
				str = (str + i + 1);
				continue ;
			}
		}
		ft_putchar_fd(*str, 1);
		sp->count += 1;
		str++;
	}
}

int	ft_printf(char const *str, ...)
{
	va_list	lst;
	char	*dup;
	t_spec	sp;

	dup = ft_strdup(str);
	sp.count = 0;
	if (dup)
	{
		va_start(lst, str);
		iter(&sp, &lst, dup);
		va_end(lst);
		free(dup);
	}
	return (sp.count);
}
