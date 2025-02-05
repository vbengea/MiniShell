/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/05 15:28:31 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

extern int SIGNAL;

void	set_history_status(int status, char ***env)
{
	char	*value;
	
	value = ft_itoa(status);
	*env = set_env("?", value, *env);
	free(value);
}

void	waiter(t_node_type type, t_ast_node *node, char ***env, int files[3])
{
	int		status;

	(void) type;
	(void) env;
	(void) files;
	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			set_history_status(status, env);
			if ((type == NODE_CMND || type == NODE_AND || type == NODE_OR) && status == 0)
				multiple_output_redirections(node);
			if (access("__INFILE__", F_OK) == 0)
			{
				unlink("__INFILE__");
			}
			if (access("__HEREDOC__", F_OK) == 0)
			{
				unlink("__HEREDOC__");
			}
			if (status != 0 && node->parent && node->parent_type == NODE_AND)
				node->parent->exit = status;
			else if (status == 0 && node->parent && node->parent_type == NODE_OR)
				node->parent->exit = status;
			break ;
		}
	}
}

static	void	preexecute(t_ast_node *node, char ***env)
{
	int		i;
	char	*str;
	char	**args;

	i = 1;
	args = ft_split(node->args[0], ' ');
	while (node->args[i])
	{
		str = node->args[i];
		node->args[i] = interpolation(str, *env);
		args = expantion(node->args[i], args);
		free(str);
		i++;
	}
	clear_arr_of_strs(node->args);
	node->args = args;
	detect_in_redirection(node);
	detect_out_redirection(node);
}

static	void	postexecute(t_ast_node *node)
{
	multiple_output_redirections(node);
	if (access("__INFILE__", F_OK) == 0)
	{
		unlink("__INFILE__");
	}
	if (node->fd)
	{
		close(node->fd);
		node->fd = -1;
	}
}

void	navigator(t_ast_node *node, char ***env, int hold, int files[3])
{
	(void) hold;
	node->exit = -1;
	if (node->left)
	{
		node->left->parent = node;
		node->left->side = 0;
		node->left->parent_type = node->type;
		selector(node->left, env, files);
	}
	if (node->right)
	{
		node->right->parent = node;
		node->right->side = 1;
		node->right->parent_type = node->type;
		selector(node->right, env, files);
	}
	if (node->type == NODE_GROUP)
		exit(0);
}

void	executor(t_ast_node *node, char ***env, int hold, int files[3])
{	
	(void) hold;
	(void) files;
	preexecute(node, env);
	if (execute(node->args, *env) == -1)
		cleanup("Error executing command..");
}

static	void	builtin(t_ast_node *node, char ***env, int hold, int files[3])
{
	(void) files;
	preexecute(node, env);
	if (ft_strncmp(node->args[0], "cd", 2) == 0)
		cd_bi(node, *env);
	else if (ft_strncmp(node->args[0], "exit", 4) == 0)
		exit_bi(node);
	else if (ft_strncmp(node->args[0], "pwd", 3) == 0)
		pwd_bi(node);
	else if (ft_strncmp(node->args[0], "env", 3) == 0)
		env_bi(node, *env, 0);
	else if (ft_strncmp(node->args[0], "export", 6) == 0)
		*env = export_bi(node, *env);
	else if (ft_strncmp(node->args[0], "unset", 5) == 0)
		*env = unset_bi(node, *env);
	else if (ft_strncmp(node->args[0], "echo", 4) == 0)
		echo_bi(node, *env);
	postexecute(node);
	set_history_status(0, env);
	if (hold)
		exit(0);
	if (node->parent)
		node->parent->exit = 0;
}

void	forker(t_ast_node *node, char ***env, void (*f)(t_ast_node *node, char ***env, int hold, int files[3]), int files[3])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		cleanup("Error forking process");
	if (pid == 0)
		f(node, env, 1, files);
	else
		waiter(node->parent_type, node, env, files);
}

void	selector(t_ast_node *node, char ***env, int files[3])
{
	if (node->type == NODE_CMND)
	{
		if (node->parent)
		{
			if (node->parent->type == NODE_AND && node->parent->exit > 0)
				return ;
			if (node->parent->type == NODE_OR && node->parent->exit == 0)
				return ;
		}
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
		pipex(node, env, files, files[2]);
	else if (node->type == NODE_GROUP)
		forker(node, env, navigator, files);
}
