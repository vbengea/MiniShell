/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/14 00:34:28 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void	export_multiple(t_ast_node *node, int len, t_terminal *tty)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (i < len && node->args[i])
	{
		key = node->args[i];
		if (ft_cmpexact(key, "export"))
		{
			key = node->args[i + 1];
			value = node->args[i + 2];
			printf("PRINTER: %s=%s\n", key, value);
			if (key)
				set_env(node, key, value, tty);
			i += 2;
		}
		i++;
	}
}

void	export_bi(t_ast_node *node, t_terminal *tty)
{
	int		len;

	len = 0;
	while (node->args[len])
		len++;
	if (len == 1)
		env_bi(node, 1, tty);
	else if (tty->env)
		export_multiple(node, len, tty);
}
