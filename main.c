/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/12 22:29:18 by jflores          ###   ########.fr       */
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
	t_token		*tokens;
	int			id;

	(void) argv;
	if (argc != 1)
	{
		printf("Incorrect number of arguments.\n");
		exit(1);
	}
	id = 0;
	env = copy_arr_of_strs(env, 0, 0);
	if (env[0] == NULL)
		env = set_env(ft_strdup("PATH"), \
			ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"), \
				env);
	load_history_from_file(env);
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
		free(input);
		t_token *tmp = tokens;
		if (!check_syntax(tmp, NULL))
		{
			// clean tokens and input
			// or maybe in reverse order. If true, run the program
			continue ;
		}
		ast = build_ast(tokens); 
		//free_token(tokens);
		assign_ids(ast, &id);
		ast_printer(ast, 0);
		if (ast)
		{
			files[0] = STDIN_FILENO;
			files[1] = STDOUT_FILENO;
			files[2] = 0;
			selector(ast, &env, files);
			free_redirect_ast(ast, 0);
		}
	}
	save_history_to_file(env);
	clear_arr_of_strs(env);
	rl_clear_history();
	free_token(tokens);
	return (0);
}
