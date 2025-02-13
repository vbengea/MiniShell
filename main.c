/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:44 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/13 21:40:56 by jflores          ###   ########.fr       */
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

void	build_terminal(char **env, t_terminal	*tty)
{
	if (tty)
	{
		tty->files[0] = STDIN_FILENO;
		tty->files[1] = STDOUT_FILENO;
		tty->files[2] = 0;
		tty->ast = NULL;
		tty->env = copy_arr_of_strs(env, 0, 0);
		if (tty->env)
		{
			if (tty->env[0] == NULL)
				tty->env = set_env(ft_strdup("PATH"), handle_no_env(), tty);
			// init_local_history(&tty->myhist);
			// load_history_from_file(&tty->myhist, tty);
			set_tty(tty);
		}
		else
		{
			perror("Error creating terminal");
			exit(1);
		}
	}
	else
	{
		perror("Error creating terminal");
		exit(1);
	}
}

static	void	destroy_terminal(t_terminal *tty)
{
	// save_history_to_file(&tty->myhist, tty);
	clear_arr_of_strs(tty->env);
	rl_clear_history();
}

int main(int argc, char **argv, char **env)
{
	char 		*input;
	t_token		*tokens;
	int			id;
	t_terminal	tty;

	(void) argv;
	if (argc != 1)
	{
		printf("Incorrect number of arguments.\n");
		exit(1);
	}
	build_terminal(env, &tty);
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
		// add_to_both_histories(&tty.myhist, input);
		tokens = tokenize_input(input);
		free(input);
		t_token *tmp = tokens;
		if (!check_syntax(tmp, NULL))
		{
			// clean tokens and input
			// or maybe in reverse order. If true, run the program
			continue ;
		}
		tty.ast = build_ast(tokens); 
		//free_token(tokens);
		if (tty.ast)
		{
			id = 0;
			assign_ids(tty.ast, &id);
			ast_printer(tty.ast, 0);
			tty.files[0] = STDIN_FILENO;
			tty.files[1] = STDOUT_FILENO;
			tty.files[2] = 0;
			selector(tty.ast, &tty);
			free_redirect_ast(tty.ast, 0);
		}
	}
	destroy_terminal(&tty);
	return (0);
}
