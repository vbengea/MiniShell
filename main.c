/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/25 17:04:50 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/headers.h"

int main(int argc, char **argv, char **env)
{
	t_token *token;
	t_ast_node *ast;
	char *input;

	(void) argc;
	(void) argv;
	while (true)
	{
		input = readline(GREEN "minishell$ " RESET);
		if (!input)
			break;

		token = tokenize_input(input);
		ast = build_ast(token);
		print_ast(ast, 0);
		selector(ast, env);
		// free(input);
		free_token(token);
		free_ast(ast);
	}
	return (0);
}