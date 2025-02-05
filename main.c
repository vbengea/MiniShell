/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/05 15:37:22 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/headers.h"

extern int SIGNAL;

int main(int argc, char **argv, char **env)
{
	t_token		*token;
	t_ast_node	*ast;
	char 		*input;

	(void) argc;
	(void) argv;
	(void) token;
	set_tty();
	env = copy_arr_of_strs(env, 0);
	while (true)
	{
		input = readline(GREEN "minishell$ " RESET);
		if (!input)
			break ;
		else if (input[0] == '\0')
			continue ;
		add_history(input);
		// token = tokenize_input(input);
		// ast = build_ast(token);
		ast = build_redirect_ast(input);
		if (ast)
		{
			// print_ast(ast, 0);
			int files[3];
			files[0] = STDIN_FILENO;
			files[1] = STDOUT_FILENO;
			files[2] = 0;
			SIGNAL = 1;
			printf("RUNNING...\n");
			selector(ast, &env, files);
			SIGNAL = -1;
			free(input);
			free_redirect_ast(ast);
		}
		//free_token(token);
	}
	clear_arr_of_strs(env);
	rl_clear_history();
	return (0);
}