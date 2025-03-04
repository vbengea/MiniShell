/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_args_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:51:46 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:10:12 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

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

t_redirect_type	get_redirection_otype(t_token_type type)
{
	if (type == TOKEN_REDIRECT_OUT)
		return (REDIRECT_OUT);
	else if (type == TOKEN_REDIRECT_IN)
		return (REDIRECT_IN);
	else if (type == TOKEN_APPEND)
		return (REDIRECT_APPEND);
	else
		return (REDIRECT_NONE);
}

void	init_cmd_args_context(t_cmd_args_context *context, \
	t_init_params *params)
{
	*params->i = 0;
	*params->prev_export = false;
	context->cmd_args = params->cmd_args;
	context->node = params->node;
	context->i = params->i;
	context->prev_export = params->prev_export;
}
