/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:37:15 by vbengea           #+#    #+#             */
/*   Updated: 2025/03/04 19:10:15 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

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
	t_token				*redirect_token;
	t_token				*filename_token;
	t_redirection_info	redir_info;

	redirect_token = *current;
	filename_token = redirect_token->next;
	if (!filename_token || filename_token->type != TOKEN_WORD)
		return (0);
	redir_info.type = get_redirect_type(redirect_token->type);
	redir_info.otype = \
		(t_out_redirect_type)get_redirection_otype(redirect_token->type);
	redir_info.file = ft_strdup(filename_token->value);
	redir_info.quote_flag = filename_token->is_quoted;
	if (!redir_info.file)
		return (0);
	add_redirection(node, &redir_info);
	*current = filename_token->next;
	return (1);
}

static bool	process_current_token(t_token *current, \
	t_cmd_args_context *context, t_ast_node *node)
{
	t_token	*temp_current;

	if (is_redirect_token(current->type))
	{
		temp_current = current;
		if (!process_redirect_token(node, &temp_current))
			return (false);
		return (true);
	}
	else if (current->type == TOKEN_WORD && current->value && current->value[0])
		process_word_token(current, context);
	else if (current->type == TOKEN_ENV_VAR
		&& current->value && current->value[0])
		process_env_var_token(current, context);
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
		if (is_redirect_token(current->type) && current->next)
			current = current->next->next;
		else
			current = current->next;
	}
	cmd_args[i] = NULL;
	return (1);
}
