/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:07:38 by vbengea           #+#    #+#             */
/*   Updated: 2025/02/07 11:42:24 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

/**
 * @warning test
 */
int main(void)
{
	t_token *token;
	t_ast_node *ast;
	char *input;

	while (true)
	{
		input = readline(GREEN "minishell$ " RESET);
		if (!input)
			break;

		token = tokenize_input(input);
		//printf("Input tokenized!\n");
		// while (token)
		// {
		// 	printf("Token type: %d, value: %s\n", token->type, token->value);
		// 	token = token->next;
		// }
		ast = build_ast(token);
		// printf("AST built!\n");

		print_ast(ast, 0);

		//free(input);
		free_token(token);
		//free_ast(ast);
	}
	return (0);
}