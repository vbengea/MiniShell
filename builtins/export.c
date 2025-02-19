/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/02/19 19:10:47 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

static	void	main_pattern(t_ast_node *node, int *i, int *to_free, \
	t_terminal *tty)
{
	char	*key;
	char	*value;

	key = node->args[*i + 1];
	value = node->args[*i + 2];
	if (!value || ft_cmpexact(value, "export"))
	{
		value = get_env(NULL, -1, key, tty);
		if (!value)
			value = "";
		else
			*to_free = 1;
		*i += 1;
	}
	else
		*i += 2;
	if (key)
	{
		value = clean_value(value, to_free);
		set_env(node, key, value, tty);
	}
}

static	void	secondary_pattern(t_ast_node *node, char *key, int *to_free, \
	t_terminal *tty)
{
	char	*value;

	value = get_env(NULL, -1, key, tty);
	if (!value)
		value = "";
	else
		*to_free = 1;
	value = clean_value(value, to_free);
	set_env(node, key, value, tty);
}

static	void	terciary_pattern(t_ast_node *node, int *to_free, \
	char **value, int *i)
{
	if (*to_free)
		free(*value);
	node->args_index = *i;
}

static	void	export_multiple(t_ast_node *node, int len, t_terminal *tty)
{
	int		i;
	char	*key;
	char	*value;
	int		export_expand;
	int		to_free;

	value = NULL;	// TODO: check in campus
	export_expand = expand_flag(node, len, &i);
	while (i < len && node->args[i])
	{
		to_free = 0;
		key = node->args[i];
		if (ft_cmpexact(key, "export"))
			main_pattern(node, &i, &to_free, tty);
		else if (key && export_expand < 2)
			secondary_pattern(node, key, &to_free, tty);
		else
		{
			terciary_pattern(node, &to_free, &value, &i);
			selector(node, tty);
			break ;
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
