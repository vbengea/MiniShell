/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/09 19:25:59 by vbengea          ###   ########.fr       */
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
		if (ast)
		{
			files[0] = STDIN_FILENO;
			selector(ast, &env, files);
			free_redirect_ast(ast, 0);
		}
		free(input);
	}
	clear_arr_of_strs(env);
	rl_clear_history();
	return (0);
}

// int main(int argc, char **argv, char **env)
// {
// 	t_ast_node	*ast;
// 	char 		*input;
// 	int			files[3];

// 	(void) argc;
// 	(void) argv;
// 	set_tty();
// 	env = copy_arr_of_strs(env, 0, 0);
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
// 		tokens = tokenize_input(input);
// 		ast = build_ast(tokens);
// 		assign_ids(ast, &id);
// 		ast_printer(ast, 0);
// 		free(input);
// 		if (ast)
// 		{
// 			files[0] = STDIN_FILENO;
// 			files[1] = STDOUT_FILENO;
// 			files[2] = 0;
// 			selector(ast, &env, files);
// 			free_redirect_ast(ast, 0);
// 		}
// 	}
// 	clear_arr_of_strs(env);
// 	rl_clear_history();
// 	return (0);
// }
