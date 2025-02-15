/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbengea < vbengea@student.42madrid.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 00:13:20 by jflores           #+#    #+#             */
/*   Updated: 2025/02/15 18:25:30 by vbengea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	build_terminal(char **env, t_terminal *tty)
{
	if (tty)
	{
		tty->files[0] = STDIN_FILENO;
		tty->files[1] = STDOUT_FILENO;
		tty->files[2] = 0;
		tty->ast = NULL;
		tty->env = copy_arr_of_strs(env, 0, 0);
		tty->env_local = malloc(sizeof(char *) * 1);
		tty->env_cmd = malloc(sizeof(char *) * 1);
		tty->env_local[0] = NULL;
		tty->env_cmd[0] = NULL;
		if (tty->env)
		{
			if (tty->env[0] == NULL)
				set_env(NULL, ft_strdup("PATH"), handle_no_env(), tty);
			init_local_history(&tty->myhist);
			load_history_from_file(&tty->myhist, tty);
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

void	assign_ids(t_ast_node *node, int *id)
{
	if (!node)
		return ;
	node->nid = ++(*id);
	assign_ids(node->left, id);
	assign_ids(node->right, id);
}

void	execute_ast(t_terminal *tty)
{
	int		id;

	if (tty->ast)
	{
		id = 0;
		assign_ids(tty->ast, &id);
		// ast_printer(tty->ast, 0);
		tty->files[0] = STDIN_FILENO;
		tty->files[1] = STDOUT_FILENO;
		tty->files[2] = 0;
		selector(tty->ast, tty);
		free_redirect_ast(tty->ast, 0);
	}
}

void	loop_terminal(t_terminal *tty)
{
	char 		*input;
	t_token		*tokens;
	t_token		*tmp;

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
		add_to_both_histories(&tty->myhist, input);
		tokens = tokenize_input(input);
		free(input);
		tmp = tokens;
		if (!check_syntax(tmp, NULL))
		{
			free_token(tmp);
			continue ;
		}
		tmp = tokens;
		tty->ast = build_ast(tokens); 
		free_token(tmp);
		execute_ast(tty);
		tty->ast = NULL;
	}
}

void	destroy_terminal(t_terminal *tty)
{
	save_history_to_file(&tty->myhist, tty);
	clear_arr_of_strs(tty->env);
	clear_arr_of_strs(tty->env_local);
	clear_arr_of_strs(tty->env_cmd);
	rl_clear_history();
}
