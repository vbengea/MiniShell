/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/18 14:54:18 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	char	*clean_value(char *value, int *to_free)
{
	char	*str;

	str = value;
	if (str[0] == '\"')
	{
		str = ft_substr(value, 1, ft_strlen(value) - 2);
		if (*to_free)
			free(value);
		*to_free = 1;
	}
	return (str);
}

static	void	export_multiple(t_ast_node *node, int len, t_terminal *tty)
{
	int		i;
	char	*key;
	char	*value;
	int		export_expand;
	int		to_free;

	i = 0;
	export_expand = node->expand_flag[0];
	while (i < len && node->args[i])
	{
		node->expand_flag[i] = export_expand;
		i++;
	}
	i = 0;
	while (i < len && node->args[i])
	{
		to_free = 0;
		key = node->args[i];
		if (ft_cmpexact(key, "export"))
		{
			key = node->args[i + 1];
			value = node->args[i + 2];
			if (!value || ft_cmpexact(value, "export"))
			{
				value = get_env(NULL, -1, key, tty);
				if (!value)
					value = "";
				else
					to_free = 1;
				i += 1;
			}
			else
				i += 2;
			if (key)
			{
				value = clean_value(value, &to_free);
				set_env(node, key, value, tty);
			}
		}
		else if (key)
		{
			value = get_env(NULL, -1, key, tty);
			if (!value)
				value = "";
			else
				to_free = 1;
			value = clean_value(value, &to_free);
			set_env(node, key, value, tty);
		}
		if (to_free)
			free(value);
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
