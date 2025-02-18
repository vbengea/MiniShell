/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea <vbengea@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:37:15 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/18 10:07:16 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"


static void process_word_token(t_token *current, t_cmd_args_context *context)
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
static void add_cmd_arg(char **cmd_args, char *value, int *i)
{
	cmd_args[*i] = ft_strdup(value);
	(*i)++;
}

static void process_env_var_token(t_token *current, t_cmd_args_context *context)
{
	char *equals_pos;
	char *name;
	char *value;
	
	if (!*context->prev_export && context->first_env_var)
	{
		add_cmd_arg(context->cmd_args, "export", context->i);
		context->first_env_var = false;
	}
	
	equals_pos = ft_strchr(current->value, '=');
	if (equals_pos)
	{
		*equals_pos = '\0';
		name = ft_strdup(current->value);
		*equals_pos = '=';
		
		value = ft_strdup(equals_pos + 1);
		
		add_cmd_arg(context->cmd_args, name, context->i);
		add_cmd_arg(context->cmd_args, value, context->i);
		
		free(name);
		free(value);
	}
	else
	{
		add_cmd_arg(context->cmd_args, current->value, context->i);
	}
}


static int	process_redirect_token(t_ast_node *node, t_token **current)
{
	return (handle_redirection(node, current));
}

int	fill_cmd_args(t_token *tokens, char **cmd_args, t_ast_node *node)
{
	t_token				*current;
	int					i;
	bool				prev_export;
	t_cmd_args_context	context;

	context.first_env_var = true;
	i = 0;
	prev_export = false;
	current = tokens;
	context.cmd_args = cmd_args;
	context.node = node;
	context.i = &i;
	context.prev_export = &prev_export;

	while (current)
	{
		if (current->type == TOKEN_WORD && current->value && current->value[0])
			process_word_token(current, &context);
		else if (current->type == TOKEN_ENV_VAR && current->value && current->value[0])
			process_env_var_token(current, &context);
		else if (is_redirect_token(current->type))
		{
			if (!process_redirect_token(node, &current))
				return (0);
		}
		current = current->next;
	}
	cmd_args[i] = NULL;
	return (1);
}
