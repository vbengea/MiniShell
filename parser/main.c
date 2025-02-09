/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:07:38 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/09 19:20:18 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	assign_ids(t_ast_node *node, int *id)
{
	if (!node)
		return ;
	if (node->type == NODE_CMND)
		node->nid = ++(*id);
	assign_ids(node->left, id);
	assign_ids(node->right, id);
	}
/**
 * @warning test
 */
int main(void)
{
	t_token *token;
	t_ast_node *ast;
	char *input;
	int	id;

	id = 0;

	while (true)
	{
		input = readline(GREEN "minishell$ " RESET);
		if (!input)
			break;

		token = tokenize_input(input);
		//printf("Input tokenized!\n");
		while (token)
		{
			printf("Token type: %d, value: %s\n", token->type, token->value);
			token = token->next;
		}
		ast = build_ast(token);
		assign_ids(ast, &id);
		// printf("AST built!\n");

		print_ast(ast, 0);

		//free(input);
		free_token(token);
		//free_ast(ast);
	}
	return (0);
}