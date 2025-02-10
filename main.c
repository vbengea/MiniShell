/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/10 19:46:53 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/headers.h"

void	assign_ids(t_ast_node *node, int *id)
{
	if (!node)
		return ;
	node->nid = ++(*id);
	assign_ids(node->left, id);
	assign_ids(node->right, id);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_ast_node	*ast;
// 	char 		*input;
// 	int			files[3];

// 	(void) argc;
// 	(void) argv;
// 	env = copy_arr_of_strs(env, 0, 0);
// 	set_tty(&env);
// 	while (true)
// 	{
// 		input = readline(GREEN "minishell$ " RESET);
// 		if (!input)
// 		{
// 			write(1, "exit\n", 5);
// 			break ;
// 		}
// 		else if (input[0] == '\0')
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		add_history(input);
// 		ast = build_redirect_ast(input);
// 		if (ast)
// 		{
// 			files[0] = STDIN_FILENO;
// 			selector(ast, &env, files);
// 			free_redirect_ast(ast, 0);
// 		}
// 		free(input);
// 	}
// 	clear_arr_of_strs(env);
// 	rl_clear_history();
// 	return (0);
// }



int main(int argc, char **argv, char **env)
{
	t_ast_node	*ast;
	char 		*input;
	int			files[3];
	t_token		*tokens;
	int			id;

	(void) argc;
	(void) argv;

	id = 0;
	load_history_from_file(env);
	env = copy_arr_of_strs(env, 0, 0);
	set_tty(&env);

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
		tokens = tokenize_input(input);
		t_token *tmp = tokens;
		if (!check_syntax(tmp, NULL))
		{
			// clean tokens and input
			// or maybe in reverse order. If true, run the program
			continue ;
		}
		ast = build_ast(tokens);
		assign_ids(ast, &id);
		// ast_printer(ast, 0);
		free(input);
		if (ast)
		{
			files[0] = STDIN_FILENO;
			files[1] = STDOUT_FILENO;
			files[2] = 0;
			selector(ast, &env, files);
			//free_redirect_ast(ast, 0);
		}
		//free_token(tokens);
	}
	save_history_to_file(env);
	clear_arr_of_strs(env);
	rl_clear_history();
	free_token(tokens);
	return (0);
}
