/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:57:15 by jflores           #+#    #+#             */
/*   Updated: 2025/02/18 22:41:53 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	tty_init(char **env, t_terminal *tty)
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
		tty->myhist = NULL;
	}
}

void	loop_inner(char *input, t_token *tokens, t_terminal *tty)
{
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
		add_to_both_histories(tty->myhist, input);
		tokens = tokenize_input(input);
		free(input);
		if (!check_syntax(tokens, NULL))
		{
			free_token(tokens);
			continue ;
		}
		tty->ast = build_ast(tokens);
		free_token(tokens);
		execute_ast(tty);
	}
}

void	exec_one(char *input, t_terminal *tty)
{
	t_token		*tokens;

	tokens = tokenize_input(input);
	if (check_syntax(tokens, NULL))
	{
		tty->ast = build_ast(tokens);
		execute_ast(tty);
	}
	free_token(tokens);
}
