/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:16:31 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/03 20:14:58 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/headers.h"

void add_redirection(t_ast_node *node, t_redirect_type type, t_out_redirect_type otype, char *file)
{
	t_redirection *new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return;

	new_redir->type = type;
	new_redir->otype = otype;
	new_redir->file = file;
	new_redir->next = NULL;

	if (!node->redirs)
	{
		node->redirs = new_redir;
	}
	else
	{
		t_redirection *current = node->redirs;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

void print_ast(t_ast_node *node, int level)
{
	if (!node)
		return;

	// Indent based on the level
	for (int i = 0; i < level; i++)
		printf("  ");

	// Print the node type
	printf("Node type: %d", node->type);

	// Print command arguments if they exist
	if (node->args)
	{
		printf(", args: ");
		for (int j = 0; node->args[j] != NULL; j++)
		{
			printf("%s ", node->args[j]);
		}
	}

	// Print redirections if they exist
	if (node->redirs)
	{
		t_redirection *redir = node->redirs;
		while (redir)
		{
			printf(", Redirect type: %d, File: %s", redir->type, redir->file);
			redir = redir->next;
		}
	}

	// End the line
	printf("\n");

	// Recursively print the left and right subtrees
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}

void	free_ast(t_ast_node *node)
{
	char	**cmd_args;
	int		i;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_CMND || node->type == NODE_REDIRECT)
	{
		cmd_args = (char **)node->args;
		if (cmd_args)
		{
			i = 0;
			while (cmd_args[i])
			{
				free(cmd_args[i]);
				i++;
			}
			free(cmd_args);
		}
	}
	free(node);
}

t_ast_node *handle_parentheses(t_token *tokens)
{
	t_token *end;
	t_token *next_after_paren;
	t_ast_node *inner;
	t_ast_node *group_node;

	end = find_matching_paren(tokens);
	if (!end || (end->next && !is_valid_operator(end->next->type) && !is_redirect_token(end->next->type)))
		return (NULL);

	next_after_paren = end->next;
	end->next = NULL;
	inner = build_ast(tokens->next);
	end->next = next_after_paren;

	group_node = create_ast_node(NODE_GROUP, NULL);
	group_node->left = inner;

	if (next_after_paren)
		return (build_operator_node(group_node, next_after_paren));

	return (group_node);
}

// t_token *find_split_point(t_token *tokens)
// {
// 	t_token *current;
// 	t_token *split_point;
// 	int min_precedence;
// 	int paren_level;

// 	current = tokens;
// 	split_point = NULL;
// 	min_precedence = 100; // Start with a high precedence value
// 	paren_level = 0;

// 	while (current)
// 	{
// 		update_paren_level(&paren_level, current->type);

// 		// Only consider operators outside parentheses
// 		if (paren_level == 0)
// 		{
// 			if ((current->type == TOKEN_AND || current->type == TOKEN_OR) && min_precedence >= 1)
// 			{
// 				min_precedence = 1;
// 				split_point = current;
// 			}
// 			else if (current->type == TOKEN_PIPE && min_precedence >= 2)
// 			{
// 				min_precedence = 2;
// 				split_point = current;
// 			}
// 			else if (is_redirect_token(current->type) && min_precedence >= 3)
// 			{
// 				min_precedence = 3;
// 				split_point = current;
// 			}
// 		}

// 		current = current->next;
// 	}

// 	return (split_point);
// }

t_token *find_split_point(t_token *tokens)
{
	t_token *current;
	t_token *split_point;
	int min_precedence;
	int paren_level;

	current = tokens;
	split_point = NULL;
	min_precedence = 100; // Start with a high precedence value
	paren_level = 0;

	while (current)
	{
		update_paren_level(&paren_level, current->type);

		// Only consider operators outside parentheses
		if (paren_level == 0)
		{
			if ((current->type == TOKEN_AND || current->type == TOKEN_OR) && min_precedence >= 1)
			{
				min_precedence = 1;
				split_point = current;
			}
			else if (current->type == TOKEN_PIPE && min_precedence >= 2)
			{
				min_precedence = 2;
				split_point = current;
			}
			else if (is_redirect_token(current->type) && min_precedence >= 3)
			{
				min_precedence = 3;
				split_point = current;
			}
		}

		// Debug print
		printf("Current token: type=%d, value=%s\n", current->type, current->value);
		printf("Split point: type=%d, value=%s\n", split_point ? split_point->type : TOKEN_INVALID, split_point ? split_point->value : "NULL");
		current = current->next;
	}

	return (split_point);
}

t_token *find_matching_paren(t_token *tokens)
{
	int paren_count;
	t_token *end;

	paren_count = 1;
	end = tokens->next;
	while (end && paren_count > 0)
	{
		if (end->type == TOKEN_OPEN_PAREN)
			paren_count++;
		else if (end->type == TOKEN_CLOSE_PAREN)
			paren_count--;
		if (paren_count > 0)
			end = end->next;
	}
	if (paren_count == 0)
		return (end);
	return (NULL);
}

t_ast_node *create_ast_node(t_node_type type, char **cmd_args)
{
	t_ast_node *node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = cmd_args;
	node->redirs = NULL;
	node->left = NULL;
	node->right = NULL;
	node->side = 0;
	return (node);
}

t_ast_node *build_operator_node(t_ast_node *left, t_token *split_point)
{
	t_ast_node *right;
	t_ast_node *root;

	root = NULL;
	right = NULL;

	// Create the operator node based on the split point type
	if (split_point->type == TOKEN_PIPE)
		root = create_ast_node(NODE_PIPE, NULL);
	else if (split_point->type == TOKEN_AND)
		root = create_ast_node(NODE_AND, NULL);
	else if (split_point->type == TOKEN_OR)
		root = create_ast_node(NODE_OR, NULL);

	// Build the right subtree
	if (split_point->next)
		right = build_ast(split_point->next);

	// Connect the left and right subtrees to the operator node
	if (root)
	{
		root->left = left;
		root->right = right;
	}

	return (root);
}

// t_ast_node *build_command_node(t_token *tokens)
// {
// 	char **cmd_args;
// 	t_token *current;
// 	int count;
// 	int i;
// 	t_ast_node *node;

// 	// Count the number of word tokens (command and arguments)
// 	count = count_word_tokens(tokens);
// 	cmd_args = malloc(sizeof(char *) * (count + 1));
// 	if (!cmd_args)
// 		return (NULL);

// 	// Copy command and arguments into cmd_args
// 	current = tokens;
// 	i = 0;
// 	while (i < count)
// 	{
// 		cmd_args[i] = ft_strdup(current->value);
// 		current = current->next;
// 		i++;
// 	}
// 	cmd_args[i] = NULL;

// 	// Create the command node
// 	node = create_ast_node(NODE_CMND, cmd_args);

// 	// Handle redirections
// 	while (current && is_redirect_token(current->type))
// 	{
// 		t_redirect_type redirect_type;
// 		t_out_redirect_type otype = STDOUT_FILE; // Default to STDOUT_FILE
// 		char *file = NULL;

// 		// Determine the type of redirection
// 		if (current->type == TOKEN_REDIRECT_IN)
// 			redirect_type = REDIRECT_IN;
// 		else if (current->type == TOKEN_REDIRECT_OUT)
// 			redirect_type = REDIRECT_OUT;
// 		else if (current->type == TOKEN_APPEND)
// 			redirect_type = REDIRECT_APPEND;
// 		else if (current->type == TOKEN_HEREDOC)
// 			redirect_type = REDIRECT_HEREDOC;

// 		// Move to the next token (the file name)
// 		current = current->next;
// 		if (current && current->type == TOKEN_WORD)
// 		{
// 			file = ft_strdup(current->value);
// 			current = current->next;
// 		}
// 		else
// 		{
// 			fprintf(stderr, "Syntax error: Expected a file after redirection operator\n");
// 			free_ast(node); // Free the AST to avoid memory leaks
// 			return (NULL);
// 		}

// 		// Add the redirection to the command node
// 		add_redirection(node, redirect_type, otype, file);
// 	}

// 	return (node);
// }


t_ast_node *build_command_node(t_token *tokens)
{
    char **cmd_args;
    t_token *current;
    int count;
    int i;
    t_ast_node *node;

    // Count the number of word tokens (command and arguments)
    count = count_word_tokens(tokens);
    cmd_args = malloc(sizeof(char *) * (count + 1));
    if (!cmd_args)
        return (NULL);

    // Copy command and arguments into cmd_args
    current = tokens;
    i = 0;
    while (i < count)
    {
        cmd_args[i] = ft_strdup(current->value);
        current = current->next;
        i++;
    }
    cmd_args[i] = NULL;

    // Create the command node
    node = create_ast_node(NODE_CMND, cmd_args);

    // Debug print
    printf("Building command node with args: ");
    for (int j = 0; cmd_args[j]; j++)
        printf("%s ", cmd_args[j]);
    printf("\n");

    // Handle redirections
    while (current && is_redirect_token(current->type))
    {
        t_redirect_type redirect_type;
        t_out_redirect_type otype = STDOUT_FILE; // Default to STDOUT_FILE
        char *file = NULL;

        // Determine the type of redirection
        if (current->type == TOKEN_REDIRECT_IN)
            redirect_type = REDIRECT_IN;
        else if (current->type == TOKEN_REDIRECT_OUT)
            redirect_type = REDIRECT_OUT;
        else if (current->type == TOKEN_APPEND)
            redirect_type = REDIRECT_APPEND;
        else if (current->type == TOKEN_HEREDOC)
            redirect_type = REDIRECT_HEREDOC;

        // Move to the next token (the file name)
        current = current->next;
        if (current && current->type == TOKEN_WORD)
        {
            file = ft_strdup(current->value);
            current = current->next;
        }
        else
        {
            fprintf(stderr, "Syntax error: Expected a file after redirection operator\n");
            free_ast(node); // Free the AST to avoid memory leaks
            return (NULL);
        }

        // Add the redirection to the command node
        add_redirection(node, redirect_type, otype, file);

        // Debug print
        printf("Added redirection: type=%d, file=%s\n", redirect_type, file);
    }

    return (node);
}


void update_paren_level(int *level, t_token_type type)
{
	if (type == TOKEN_OPEN_PAREN)
		(*level)++;
	else if (type == TOKEN_CLOSE_PAREN)
		(*level)--;
}

void update_split_point(t_token **split, t_token *current, int *min_prec)
{
	if ((current->type == TOKEN_AND || current->type == TOKEN_OR) && *min_prec >= 1)
	{
		*min_prec = 1;
		*split = current;
	}
	else if (current->type == TOKEN_PIPE && *min_prec >= 2)
	{
		*min_prec = 2;
		*split = current;
	}
	else if (is_redirect_token(current->type) && *min_prec >= 3)
	{
		*min_prec = 3;
		*split = current;
	}
}

int count_word_tokens(t_token *tokens)
{
	int count;
	t_token *current;

	count = 0;
	current = tokens;
	while (current && current->type == TOKEN_WORD)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void disconnect_tokens(t_token *start, t_token *split)
{
	t_token *prev;

	prev = start;
	while (prev->next != split)
		prev = prev->next;
	prev->next = NULL;
}

void reconnect_tokens(t_token *start, t_token *split)
{
	t_token *prev;

	prev = start;
	while (prev->next != NULL)
		prev = prev->next;
	prev->next = split;
}

int is_valid_operator(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR);
}

int is_redirect_token(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT || type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

// t_ast_node *build_ast(t_token *tokens)
// {
// 	t_token *split_point;
// 	t_ast_node *left;

// 	if (!tokens)
// 		return (NULL);

// 	// Handle parentheses
// 	if (tokens->type == TOKEN_OPEN_PAREN)
// 		return (handle_parentheses(tokens));

// 	// Find the split point (lowest precedence operator)
// 	split_point = find_split_point(tokens);
// 	if (!split_point)
// 		return (build_command_node(tokens));

// 	// Build the left subtree
// 	left = NULL;
// 	if (split_point != tokens)
// 	{
// 		disconnect_tokens(tokens, split_point);
// 		left = build_ast(tokens);
// 		reconnect_tokens(tokens, split_point);
// 	}

// 	// Build the operator node and connect the subtrees
// 	return (build_operator_node(left, split_point));
// }

t_ast_node *build_ast(t_token *tokens)
{
	t_token *split_point;
	t_ast_node *left;

	if (!tokens)
		return (NULL);

	// Handle parentheses
	if (tokens->type == TOKEN_OPEN_PAREN)
		return (handle_parentheses(tokens));

	// Find the split point (lowest precedence operator)
	split_point = find_split_point(tokens);
	if (!split_point)
	{
		printf("No split point found, building command node\n");
		return (build_command_node(tokens));
	}

	// Debug print
	printf("Split point found: type=%d, value=%s\n", split_point->type, split_point->value);

	// Build the left subtree
	left = NULL;
	if (split_point != tokens)
	{
		printf("Building left subtree\n");
		disconnect_tokens(tokens, split_point);
		left = build_ast(tokens);
		reconnect_tokens(tokens, split_point);
	}

	// Build the operator node and connect the subtrees
	printf("Building operator node\n");
	return (build_operator_node(left, split_point));
}