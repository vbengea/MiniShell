/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:51:07 by juandanielf       #+#    #+#             */
/*   Updated: 2024/10/30 09:30:49 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*get_chopped(t_spec *sp, size_t len)
{
	char	*chopped;
	size_t	original;

	original = ft_strlen(sp->str);
	chopped = ft_calloc(len + 1, 1);
	if (chopped)
	{
		ft_memset(chopped, ' ', len);
		if (ft_strchr("diuxX", sp->conversion))
			ft_memset(chopped, '0', len);
		if (sp->conversion == 's')
			ft_strlcpy(chopped, sp->str, len + 1);
		else if (original <= len)
			ft_strlcpy((chopped + len - original), sp->str, original + 1);
		if (get_pad(sp) == ' ')
			prepad(sp, chopped);
		free(sp->str);
		sp->str = NULL;
		return (chopped);
	}
	return (NULL);
}

static	void	relen(t_spec *sp, size_t *len)
{
	if (is_zero(sp->str) && (sp->precision == 0 || \
		(sp->precision == -1 && sp->is_precision_dot)))
		*len = 0;
	if (!ft_strnstr(sp->str, "(nil)", 5))
	{
		if (sp->precision != -1 && sp->conversion == 's' && \
			sp->precision <= (int)*len)
			*len = sp->precision;
		else if (sp->precision != -1 && sp->precision > (int)*len && \
			sp->conversion != 's')
			*len = sp->precision;
		if (ft_strchr("pxX", sp->conversion) && \
			sp->flag_pound && !is_zero(sp->str))
			*len += 2;
		if (ft_strchr("di", sp->conversion) && \
			(!sp->is_positive || sp->flag_space || sp->flag_plus))
			*len += 1;
	}
}

static	void	pad_str_copy(t_spec *sp, \
	size_t *len, size_t padding, size_t total)
{
	size_t	i;
	size_t	j;

	*len = ft_strlen(sp->base);
	j = 0;
	if (sp->flag_minus)
	{
		i = 0;
		while (i < *len)
		{
			sp->str[i] = sp->base[j];
			i++;
			j++;
		}
	}
	else
	{
		i = padding;
		while (i < total)
		{
			sp->str[i] = sp->base[j];
			i++;
			j++;
		}
	}
}

static	void	pad_str_helper(t_spec *sp, size_t *len, \
	size_t padding, size_t total)
{
	ft_memset(sp->str, get_pad(sp), total);
	if (sp->conversion == 'c')
		(void)len;
	else
		pad_str_copy(sp, len, padding, total);
	if (get_pad(sp) != ' ')
		prepad(sp, sp->str);
	if (sp->base)
		free(sp->base);
	sp->base = NULL;
}

void	pad_str(t_spec *sp)
{
	size_t	len;
	size_t	total;
	size_t	padding;

	if (validate(sp))
	{
		padding = 0;
		len = ft_strlen(sp->str);
		relen(sp, &len);
		total = len;
		sp->base = get_chopped(sp, len);
		if (sp->base)
		{
			if (sp->width > len)
				total = sp->width;
			if (!sp->flag_minus)
				padding = total - len;
			sp->str = ft_calloc(total + 1, 1);
			if (sp->str)
				pad_str_helper(sp, &len, padding, total);
		}
	}
}
