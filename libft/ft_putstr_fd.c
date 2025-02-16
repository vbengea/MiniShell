/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:57:13 by juandanielf       #+#    #+#             */
/*   Updated: 2025/02/16 11:52:11 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		ft_putchar_fd(*s++, fd);
}

void	ft_putstrnl_fd(char *s, int fd)
{
	while (*s)
		ft_putchar_fd(*s++, fd);
	ft_putchar_fd('\n', fd);
}
