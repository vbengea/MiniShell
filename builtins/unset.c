/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/14 00:35:55 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*unset_str(char *key, int len)
{
	char	*str;

	str = malloc(len + 1 + 1);
	if (str)
	{
		ft_strcpy(str, key);
		str[len] = '=';
		str[len + 1] = '\0';
	}
	return (str);
}

void	unset_bi(t_ast_node *node, t_terminal *tty)
{
	int		i;
	int		len;
	char	*str;

	len = ft_strlen(node->args[1]);
	str = unset_str(node->args[1], len);
	i = 0;
	while (tty->env && tty->env[i])
	{
		if (ft_strnstr(tty->env[i], str, len + 1))
		{
			free(tty->env[i]);
			while (tty->env && tty->env[i])
			{
				tty->env[i] = tty->env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
	free(str);
	tty->env = copy_arr_of_strs(tty->env, 0, 1);
}
