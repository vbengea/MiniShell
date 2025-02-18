/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:07:58 by jflores           #+#    #+#             */
/*   Updated: 2025/02/18 22:03:21 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

char	*clean_value(char *value, int *to_free)
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

int	validate_cmd_level(t_ast_node *node)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (node->args[i])
	{
		key = node->args[i];
		if (ft_cmpexact(key, "export"))
		{
			key = node->args[i + 1];
			value = node->args[i + 2];
			if (!value || ft_cmpexact(value, "export"))
				i += 1;
			else
				i += 2;
		}
		else if (key)
			return (0);
		i++;
	}
	return (1);
}

int	expand_flag(t_ast_node *node, int len, int *j)
{
	int		i;
	int		export_expand;

	i = 0;
	*j = 0;
	export_expand = node->expand_flag[0];
	if (export_expand == 0 && !validate_cmd_level(node))
		export_expand = 2;
	while (i < len && node->args[i])
	{
		node->expand_flag[i] = export_expand;
		i++;
	}
	return (export_expand);
}
