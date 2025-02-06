/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/06 20:38:51 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/headers.h"

volatile sig_atomic_t g_running = 1;

int main(int argc, char **argv, char **env)
{
	t_token		*token;
	t_ast_node	*ast;
	char 		*input;

	(void) argc;
	(void) argv;
	(void) token;
	set_tty();
	env = copy_arr_of_strs(env, 0, 0);
	while (true)
	{
		input = readline(GREEN "minishell$ " RESET);
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		else if (input[0] == '\0')
			continue ;
		add_history(input);
		// token = tokenize_input(input);
		// ast = build_ast(token);
		// print_ast(ast, 0);
		ast = build_redirect_ast(input);
		if (ast)
		{
			int files[3];
			files[0] = STDIN_FILENO;
			files[1] = STDOUT_FILENO;
			files[2] = 0;
			selector(ast, &env, files);
			free(input);
			free_redirect_ast(ast);
		}
		//free_token(token);
	}
	clear_arr_of_strs(env);
	rl_clear_history();
	return (0);
}