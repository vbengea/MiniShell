/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_funcitons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:55:07 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/23 09:37:55 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/data_structure.h"
#include <stdlib.h>
#include <string.h>

t_ast_node *create_cmnd_node(char **args)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_CMND;
	node->args = args;
	node->file = NULL;
	node->redirect_type = 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node *create_redir_node(int type, char *file, t_ast_node *left)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_REDIRECT;
	node->args = NULL;
	node->file = strdup(file);
	node->redirect_type = type;
	node->left = left;
	node->right = NULL;
	return (node);
}

t_ast_node *create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));

	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->args = NULL;
	node->file = NULL;
	node->redirect_type = 0;
	node->left = left;
	node->right = right;
	return (node);
}



// cat < input.txt  | grep "text" | sort > output.txt
void	print_ast(t_ast_node *node, int indent);


int main(void)
{
	char	*cat_args[] = {"cat", NULL};
	char	*grep_args[] = {"grep", "text", NULL};
	char	*sort_args[] = {"sort", NULL};


	// Command nodes
	t_ast_node	*cat_node = create_cmnd_node(cat_args);
	t_ast_node	*grep_node = create_cmnd_node(grep_args);
	t_ast_node	*sort_node = create_cmnd_node(sort_args);

	// Redirection nodes
	t_ast_node *redir_in = create_redir_node(2, "input.txt", cat_node);
	t_ast_node *redir_out = create_redir_node(1, "output.txt", sort_node);

	//Pipe nodes
	t_ast_node	*pipe1 = create_pipe_node(redir_in, grep_node);
	t_ast_node	*pipe2 = create_pipe_node(pipe1, redir_out);

	// Root of AST is now pipe2
	print_ast(pipe2, 0);
	return (0);
}