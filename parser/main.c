/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:07:38 by vbengea           #+#    #+#             */
/*   Updated: 2025/01/26 13:08:54 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void print_ast(t_ast_node *node, int level)
{
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("Node type: %d", node->type);
	if (node->args)
	{
		printf(", args: ");
		for (int j = 0; node->args[j] != NULL; j++)
		{
			printf("%s ", node->args[j]);
		}
	}
	printf("\n");
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}

int main(void)
{
	t_token	*token;
	t_ast_node	*ast;
	char *input;

	while (true)
	{
		input = readline("minishell$ ");
		if (!input)
			break;

		token = tokenize_input(input);
		printf("Input tokenized!\n");

		ast = build_ast(token);
		printf("AST built!\n");

		print_ast(ast, 0);

		free(input);
		free_token(token);
		// free_ast(ast);
	}
	return (0);
}