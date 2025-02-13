/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/13 18:41:17 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

extern int SIGNAL;

void	set_history_status(int status, t_terminal *tty)
{
	char	*value;
	
	value = ft_itoa(status);
	if (value && tty->env)
	{
		tty->env = set_env("?", value, tty);
		free(value);
	}
}

void	waiter_util(t_ast_node *node, int status, t_terminal *tty)
{
	char	*file;

	if (node->parent)
		node->parent->exit = status;
	node->exit = status;
	set_history_status(status, tty);
	if (status == 0)
		multiple_output_redirections(node);
	file = tmp_path(node->nid, REDIRECT_IN);
	if (file)
	{
		if (access(file, F_OK) == 0)
			unlink(file);
		free(file);
	}
	file = tmp_path(node->nid, REDIRECT_HEREDOC);
	if (file)
	{
		if (access(file, F_OK) == 0)
			unlink(file);
		free(file);
	}
}

void	waiter(t_ast_node *node, t_terminal *tty)
{
	int		status;

	status = 0;
	setup_signal_handlers_process();
	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			waiter_util(node, status, tty);
			break ;
		}
	}
}

void	parse_command(t_ast_node *node, t_terminal *tty)
{
	int		i;
	char	*str;
	char	**args;

	if (node->type == NODE_CMND && node->args[0] != NULL)
	{
		i = 0;
		args = ft_split(" ", ' ');
		while (node->args[i])
		{
			if (node->expand_flag[i] == 1)
			{
				str = interpolation(node->args[i++], tty);
				args = expantion(str, args);
				free(str);
			}
			else
			{
				str = node->args[i++];
				args = expantion(str, args);
			}
		}
		clear_arr_of_strs(node->args);
		node->args = args;
	}
}

static	void	preexecute(t_ast_node *node, t_terminal *tty)
{
	parse_command(node, tty);
	detect_in_redirection(node, tty);
	detect_out_redirection(node);
}

static	void	postexecute(t_ast_node *node)
{
	char	*file;

	multiple_output_redirections(node);
	file = tmp_path(node->nid, REDIRECT_IN);
	if (file)
	{
		if (access(file, F_OK) == 0)
			unlink(file);
		free(file);
	}
	if (node->in_fd >= 0 && node->has_group_in_fd == 0)
	{
		close(node->in_fd);
		node->in_fd = -1;
	}
	if (node->out_fd >= 0 && node->has_group_out_fd == 0)
	{
		close(node->out_fd);
		node->out_fd = -1;
	}
}

void	navigator_init(t_ast_node *node, t_terminal *tty)
{
	if (node->left)
	{
		node->left->parent = node;
		node->left->side = 0;
		node->left->parent_type = node->type;
		selector(node->left, tty);
	}
	if (node->right)
	{
		node->right->parent = node;
		node->right->side = 1;
		node->right->parent_type = node->type;
		selector(node->right, tty);
	}
}

void	navigator(t_ast_node *node, int hold, t_terminal *tty)
{
	(void) hold;
	navigator_init(node, tty);
	if (node->type == NODE_GROUP)
	{
		if (node->in_fd >= 0)
		{
			close(node->in_fd);
			node->in_fd = -1;
		}
		if (node->out_fd >= 0)
		{
			close(node->out_fd);
			node->out_fd = -1;
		}
		free_redirect_ast(node, 1);
		clear_arr_of_strs(tty->env);
		exit(0);
	}
}

void	executor(t_ast_node *node, int hold, t_terminal *tty)
{	
	(void) hold;
	setup_signal_handlers_child();
	preexecute(node, tty);
	if (execute(node->args, tty) == -1)
		cleanup("Error executing command..");
}

static	void	builtin_end(t_ast_node *node, int hold, t_terminal *tty)
{
	set_history_status(0, tty);
	if (node->parent)
		node->parent->exit = 0;
	if (hold)
		exit(1);
}

static	int		check_options(t_ast_node *node, int hold, t_terminal *tty)
{
	int	i;

	i = 1;
	if (node->args[0] == NULL)
		return (1);
	while (node->args[i])
	{
		if (node->args[i][0] == '-')
		{
			if (ft_strncmp(node->args[0], "echo", 4) == 0 && \
				node->args[i][1] == 'n' && ft_strlen(node->args[i]) == 2)
				break ;
			else
			{
				printf("%s: %s: invalid option\n", node->args[0], \
					node->args[i]);
				builtin_end(node, hold, tty);
				return (0);
			}
		}
		else
			break ;
		i++;
	}
	return (1);
}

static	void	builtin(t_ast_node *node, int hold, t_terminal *tty)
{
	(void) tty;
	if (check_options(node, hold, tty))
	{
		preexecute(node, tty);
		if (node->args[0] == NULL)
			(void) hold;
		else if (ft_strncmp(node->args[0], "cd", 2) == 0)
			cd_bi(node, tty);
		else if (ft_strncmp(node->args[0], "exit", 4) == 0)
			exit_bi(node, tty);
		else if (ft_strncmp(node->args[0], "pwd", 3) == 0)
			pwd_bi(node);
		else if (ft_strncmp(node->args[0], "env", 3) == 0)
			env_bi(node, 0, tty);
		else if (ft_strncmp(node->args[0], "export", 6) == 0)
			tty->env = export_bi(node, tty);
		else if (ft_strncmp(node->args[0], "unset", 5) == 0)
			tty->env = unset_bi(node, tty);
		else if (ft_strncmp(node->args[0], "echo", 4) == 0)
			echo_bi(node);
		postexecute(node);
		builtin_end(node, hold, tty);
	}
}

void	forker(t_ast_node *node, void (*f)(t_ast_node *node, int hold, t_terminal *tty), t_terminal *tty)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		cleanup("Error forking process");
	if (pid == 0)
		f(node, 1, tty);
	else
		waiter(node, tty);
}

void	selector_node(t_ast_node *node, t_terminal *tty)
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
			forker(node, builtin, tty);
		else
			builtin(node, 0, tty);
	}
	else
		forker(node, executor, tty);
}

void	selector_pipe(t_ast_node *node, t_terminal *tty)
{
	t_ast_node	*parent;

	tty->files[2] = node->nid;
	while (node->left != NULL)
	{
		parent = node;
		if (node->right)
		{
			node->right->parent = parent;
			node->right->side = 1;
		}
		node->left->parent = parent;
		node->left->side = 0;
		node = node->left;
		if (node->type == NODE_GROUP && node->parent->type == NODE_GROUP)
			return ;
	}
	SIGNAL = 3;
	pipex(node, tty);
}

void	selector(t_ast_node *node, t_terminal *tty)
{
	if (node->type == NODE_CMND)
		selector_node(node, tty);
	else if (node->type == NODE_AND || node->type == NODE_OR)
		navigator(node, 1, tty);
	else if (node->type == NODE_PIPE)
		selector_pipe(node, tty);
	else if (node->type == NODE_GROUP && \
		(!node->parent || node->parent->type != NODE_GROUP))
	{
		preexecute(node, tty);
		forker(node, navigator, tty);
	}
}
