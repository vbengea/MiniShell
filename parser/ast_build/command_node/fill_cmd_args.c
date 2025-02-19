/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:37:15 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/19 13:05:43 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/headers.h"

static void	process_env_var_token(t_token *current, t_cmd_args_context *context)
{
	char	*equals_pos;

	if (!current || !context || !context->cmd_args || !context->i)
		return ;
	if (!*context->prev_export)
		add_cmd_arg(context->cmd_args, "export", context->i);
	equals_pos = ft_strchr(current->value, '=');
	if (equals_pos)
		process_env_var_with_equals(current, context, equals_pos);
	else
		add_cmd_arg(context->cmd_args, current->value, context->i);
	*context->prev_export = false;
}

static int	process_redirect_token(t_ast_node *node, t_token **current)
{
	return (handle_redirection(node, current));
}

static void	init_cmd_args_context(t_cmd_args_context *context, \
	t_init_params *params)
{
	*params->i = 0;
	*params->prev_export = false;
	context->cmd_args = params->cmd_args;
	context->node = params->node;
	context->i = params->i;
	context->prev_export = params->prev_export;
}

static bool	process_current_token(t_token *current, \
	t_cmd_args_context *context, t_ast_node *node)
{
	if (current->type == TOKEN_WORD && current->value && current->value[0])
		process_word_token(current, context);
	else if (current->type == TOKEN_ENV_VAR
		&& current->value && current->value[0])
		process_env_var_token(current, context);
	else if (is_redirect_token(current->type))
	{
		if (!process_redirect_token(node, &current))
			return (false);
	}
	return (true);
}

int	fill_cmd_args(t_token *tokens, char **cmd_args, t_ast_node *node)
{
	t_token				*current;
	int					i;
	bool				prev_export;
	t_cmd_args_context	context;
	t_init_params		params;

	params = (t_init_params){cmd_args, node, &i, &prev_export};
	init_cmd_args_context(&context, &params);
	current = tokens;
	while (current)
	{
		if (!process_current_token(current, &context, node))
			return (0);
		current = current->next;
	}
	cmd_args[i] = NULL;
	return (1);
}
