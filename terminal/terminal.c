/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 00:13:20 by jflores           #+#    #+#             */
/*   Updated: 2025/02/23 10:34:57 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	build_terminal(char **env, t_terminal *tty, int do_history)
{
	if (tty)
	{
		tty_init(env, tty);
		if (tty->env)
		{
			if (tty->env[0] == NULL)
				set_env(NULL, ft_strdup("PATH"), handle_no_env(), tty);
			if (do_history)
			{
				tty->myhist = init_local_history();
				load_history_from_file(tty->myhist, tty);
			}
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
	int		i;

	if (tty->ast)
	{
		id = 0;
		assign_ids(tty->ast, &id);
		ast_printer(tty->ast, 0);
		tty->files[0] = STDIN_FILENO;
		tty->files[1] = STDOUT_FILENO;
		tty->files[2] = 0;
		selector(tty->ast, tty);
		free_redirect_ast(tty->ast, 0);
		i = 0;
		while (tty->env_cmd[i])
		{
			free(tty->env_cmd[i]);
			i++;
		}
		tty->env_cmd[0] = NULL;
	}
	tty->ast = NULL;
	tty->exit = -1;
}

void	loop_terminal(t_terminal *tty)
{
	char		*input;
	t_token		*tokens;

	input = NULL;
	tokens = NULL;
	loop_inner(input, tokens, tty);
}

void	destroy_terminal(t_terminal *tty)
{
	if (tty->prompt)
		free(tty->prompt);
	save_history_to_file(tty->myhist, tty);
	clear_arr_of_strs(tty->env);
	clear_arr_of_strs(tty->env_local);
	clear_arr_of_strs(tty->env_cmd);
	rl_clear_history();
}
