/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea <vbengea@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/29 09:20:33 by vbengea          ###   ########.fr       */
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
	(void) token;
	while (true)
	{
		input = readline(GREEN "minishell$ " RESET);
		if (!input)
			break;
		token = tokenize_input(input);
		ast = build_ast(token);
		print_ast(ast, 0);
		int files[3];
		files[0] = STDIN_FILENO;
		files[1] = STDOUT_FILENO;
		files[2] = 0;
		selector(ast, env, files);
		// free(input);
		//free_token(token);
		//free_ast(ast);
	}
	return (0);
}