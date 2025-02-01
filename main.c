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

extern int SIGNAL;

int main(int argc, char **argv, char **env)
{
	t_token		*token;
	t_ast_node	*ast;
	char 		*input;

	(void) argc;
	(void) argv;
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
		token = tokenize_input(input);
		ast = build_ast(token);
		int files[3];
		files[0] = STDIN_FILENO;
		files[1] = STDOUT_FILENO;
		files[2] = 0;
		SIGNAL = 1;
		selector(ast, &env, files);
		SIGNAL = -1;
		free(input);
		//free_token(token);
		//free_ast(ast);
	}
	clear_arr_of_strs(env);
	rl_clear_history();
	return (0);
}