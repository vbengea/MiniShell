/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/07 04:16:56 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/headers.h"

volatile sig_atomic_t g_running = 1;

int main(int argc, char **argv, char **env)
{
	t_ast_node	*ast;
	char 		*input;
	int			files[3];

	(void) argc;
	(void) argv;
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
		{
			free(input);
			continue ;
		}
		add_history(input);
		ast = build_redirect_ast(input);
		free(input);
		if (ast)
		{
			files[0] = STDIN_FILENO;
			files[1] = STDOUT_FILENO;
			files[2] = 0;
			selector(ast, &env, files);
			free_redirect_ast(ast, 0);
		}
	}
	clear_arr_of_strs(env);
	rl_clear_history();
	return (0);
}