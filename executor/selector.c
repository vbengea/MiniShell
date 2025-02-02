/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/25 16:31:33 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

extern int SIGNAL;

void	navigator(t_ast_node *node, char ***env, int hold, int files[3])
{
	(void) hold;
	if (node->left)
	{
		node->left->parent = node;
		node->left->side = 0;
		selector(node->left, env, files);
	}
	if (node->right)
	{
		node->right->parent = node;
		node->right->side = 1;
		selector(node->right, env, files);
	}
	if (node->type == NODE_GROUP || node->type == NODE_REDIRECT)
		exit(0);
}

void	executor(t_ast_node *node, char ***env, int hold, int files[3])
{
	(void) hold;
	(void) files;
	if (execute(node->args, *env) == -1)
		cleanup("Error executing command..");
}

static	void	builtin(t_ast_node *node, char ***env, int hold, int files[3])
{
	(void) files;
	if (ft_strncmp(node->args[0], "cd", 2) == 0)
		cd_bi(node->args[1], *env);
	else if (ft_strncmp(node->args[0], "exit", 4) == 0)
		exit_bi();
	else if (ft_strncmp(node->args[0], "pwd", 3) == 0)
		pwd_bi();
	else if (ft_strncmp(node->args[0], "env", 3) == 0)
		env_bi(*env, 0);
	else if (ft_strncmp(node->args[0], "export", 6) == 0)
		*env = export_bi(node->args[1], node->args[2], *env);
	else if (ft_strncmp(node->args[0], "unset", 5) == 0)
		*env = unset_bi(node->args[1], *env);
	else if (ft_strncmp(node->args[0], "echo", 4) == 0)
		echo_bi(node->args, *env);
	if (hold)
		exit(0);
}

void	forker(t_ast_node *node, char ***env, void (*f)(t_ast_node *node, char ***env, int hold, int files[3]), int files[3])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		cleanup("Error forking process");
	if (pid == 0)
	{
		f(node, env, 1, files);
	}
	else
		waiter(node->parent_type);
}

void	selector(t_ast_node *node, char ***env, int files[3])
{
	if (node->type == NODE_CMND)
	{
		if (is_builtin(node))
		{
			if (is_pipe_state(node))
				forker(node, env, builtin, files);
			else
				builtin(node, env, 0, files);
		}
		else
			forker(node, env, executor, files);
	}
	else if (node->type == NODE_AND || node->type == NODE_OR)
		navigator(node, env, 1, files);
	else if (node->type == NODE_PIPE)
	{
		pipex(node, env, files, files[2]);
		waiter(node->type);
	}
	else if (node->type == NODE_GROUP)
		forker(node, env, navigator, files);
	else if (node->type == NODE_REDIRECT)
		forker(node, env, redirecter, files);
}
