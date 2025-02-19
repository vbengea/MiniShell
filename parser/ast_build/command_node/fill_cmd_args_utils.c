/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_args_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:51:46 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 13:07:58 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"

void	process_word_token(t_token *current, t_cmd_args_context *context)
{
	if (ft_strcmp(current->value, "export") == 0)
	{
		if (!*context->prev_export)
		{
			*context->prev_export = true;
			handle_word(current, context->cmd_args, context->node, context->i);
		}
	}
	else
	{
		handle_word(current, context->cmd_args, context->node, context->i);
		*context->prev_export = false;
	}
}

void	add_cmd_arg(char **cmd_args, char *value, int *i)
{
	if (!cmd_args || !value || !i)
		return ;
	cmd_args[*i] = ft_strdup(value);
	if (cmd_args[*i])
		(*i)++;
}

void	process_env_var_with_equals(t_token *current, \
	t_cmd_args_context *context, char *equals_pos)
{
	char	*name;
	char	*value;

	*equals_pos = '\0';
	name = ft_strdup(current->value);
	*equals_pos = '=';
	if (!name)
		return ;
	value = ft_strdup(equals_pos + 1);
	if (!value)
	{
		free(name);
		return ;
	}
	add_cmd_arg(context->cmd_args, name, context->i);
	add_cmd_arg(context->cmd_args, value, context->i);
	free(name);
	free(value);
}
