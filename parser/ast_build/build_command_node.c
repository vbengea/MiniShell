/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:43:41 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/15 18:11:21 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

void process_word_token(t_token *current, t_cmd_args_context *context)
{
	handle_word(current, context->cmd_args, context->node, context->i);
	*context->prev_export = (ft_strcmp(current->value, "export") == 0);
}

void process_env_var_token(t_token *current, t_cmd_args_context *context)
{
	if (!*context->prev_export)
		handle_env_var(current, context->cmd_args, context->node, context->i);
	*context->prev_export = false;
}

int process_redirect_token(t_ast_node *node, t_token **current)
{
	return handle_redirection(node, current);
}

int	cmd_args_loop(t_token *current, t_cmd_args_context *context, t_ast_node *node)
{
	while (current)
	{
		if (current->type == TOKEN_WORD && current->value && current->value[0])
			process_word_token(current, context);
		else if (current->type == TOKEN_ENV_VAR && current->value && current->value[0])
			process_env_var_token(current, context);
		else if (is_redirect_token(current->type))
		{
			if (!process_redirect_token(node, &current))
				return (0);
		}
		current = current->next;
	}
	return (1);
}


int fill_cmd_args(t_token *tokens, char **cmd_args, t_ast_node *node)
{
	t_token *current;
	int i;
	bool prev_export;
	t_cmd_args_context context;

	i = 0;
	prev_export = false;
	current = tokens;
	context.cmd_args = cmd_args;
	context.node = node;
	context.i = &i;
	context.prev_export = &prev_export;
	if (!cmd_args_loop(current, &context, node))
		return (0);
	cmd_args[i] = NULL;
	return (1);
}

void free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void handle_word_token(t_token *temp, int *count, bool *prev_export)
{
	(*count)++;
	*prev_export = (temp->value && ft_strcmp(temp->value, "export") == 0);
}

bool handle_env_var_token(bool prev_export, int *count)
{
	if (!prev_export)
		(*count)++;
	*count += 2;
	return (true);
}

bool handle_redirect_count(t_token **temp)
{
	*temp = (*temp)->next;
	if (!temp || (*temp)->type != TOKEN_WORD)
		return (false);
	return (true);
}

int count_command_words(t_token *tokens)
{
	bool prev_export;
	t_token *temp;
	int count;

	count = 0;
	prev_export = false;
	temp = tokens;
	while (temp)
	{
		if (temp->type == TOKEN_WORD)
			handle_word_token(temp, &count, &prev_export);
		else if (temp->type == TOKEN_ENV_VAR)
			prev_export = handle_env_var_token(prev_export, &count);
		else if (is_redirect_token(temp->type))
		{
			if (!handle_redirect_count(&temp))
				return (-1);
		}
		temp = temp->next;
	}
	return (count);
}

char **allocate_cmd_args(int count)
{
	char **cmd_args;

	cmd_args = malloc(sizeof(char *) * (count + 1));
	if (!cmd_args)
		return (NULL);
	return (cmd_args);
}

t_redirect_type get_redirect_type(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN)
		return (REDIRECT_IN);
	if (type == TOKEN_REDIRECT_OUT)
		return (REDIRECT_OUT);
	if (type == TOKEN_APPEND)
		return (REDIRECT_APPEND);
	return (REDIRECT_HEREDOC);
}

void process_env_tokens(char **env_tokens, char **cmd_args, t_ast_node *node, int *i)
{
	int j;

	j = 0;
	while (env_tokens[j])
	{
		node->expand_flag[*i] = 1;
		cmd_args[*i] = ft_strdup(env_tokens[j]);
		(*i)++;
		j++;
	}
}

void handle_env_var(t_token *current, char **cmd_args, t_ast_node *node, int *i)
{
	char **env_tokens;

	cmd_args[*i] = ft_strdup("export");
	(*i)++;
	env_tokens = ft_split(current->value, '=');
	process_env_tokens(env_tokens, cmd_args, node, i);
	free_tab(env_tokens);
}

void handle_word(t_token *current, char **cmd_args, t_ast_node *node, int *i)
{
	cmd_args[*i] = ft_strdup(current->value);
	if (current->type == TOKEN_ENV_VAR || current->has_env)
		node->expand_flag[*i] = 1;
	if (current->has_space)
		node->has_space[*i] = 1;
	(*i)++;
}

int handle_redirection(t_ast_node *node, t_token **current)
{
	t_redirection_info	redir_info;
	t_token				*next;

	redir_info.otype = STDOUT_FILE;
	redir_info.type = get_redirect_type((*current)->type);
	next = (*current)->next;
	if (!next || next->type != TOKEN_WORD)
		return (0);
	*current = next;
	redir_info.file = ft_strdup((*current)->value);
	redir_info.quote_flag = (*current)->is_quoted;
	add_redirection(node, &redir_info);
	return (1);
}

t_ast_node *build_command_node(t_token *tokens)
{
	t_ast_node	*node;
	char		**cmd_args;
	int			count;

	node = create_ast_node(NODE_CMND, NULL);
	if (!node)
		return (NULL);
	count = count_command_words(tokens);
	if (count < 0)
		return (NULL);
	cmd_args = allocate_cmd_args(count);
	if (!cmd_args)
		return (NULL);
	if (!fill_cmd_args(tokens, cmd_args, node))
		return (NULL);
	node->args = cmd_args;
	return (node);
}