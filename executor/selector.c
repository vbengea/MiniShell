/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:10:56 by juaflore          #+#    #+#             */
/*   Updated: 2025/02/18 18:11:32 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

extern int	g_sig;

void	set_history_status(int status, t_terminal *tty)
{
	char	*value;

	value = ft_itoa(status);
	if (value && tty->env)
	{
		set_env(NULL, "?", value, tty);
		free(value);
	}
}

void	waiter_util(t_ast_node *node, int status, t_terminal *tty)
{
	char		*file;
	t_ast_node	*parent;

	if (status >= SIGHUP && status <= (SIGSYS + 33))
		status += 128;
	else if (status > 256)
		status = status >> 8;
	parent = node->parent;
	while (parent)
	{
		parent->exit = status;
		parent = parent->parent;
	}
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
}

void	waiter(t_ast_node *node, t_terminal *tty)
{
	int		status;

	status = 0;
	g_sig = 1;
	while (1)
	{
		if (waitpid(-1, &status, 0) > 0)
		{
			if (status != SIGINT)
				g_sig = 0;
			waiter_util(node, status, tty);
			break ;
		}
	}
}

void	parse_command(t_ast_node *node, t_terminal *tty)
{
	int		i;
	int		j;
	char	*str;
	char	**args;
	char	**inter;

	if (node->type == NODE_CMND && node->args[0] != NULL)
	{
		i = node->args_index;
		args = ft_split(" ", ' ');
		while (node->args[i])
		{
			if (node->expand_flag[i] == 1)
			{
				str = interpolation(node->args[i], i, tty);
				inter = ft_split(str, ' ');
				free(str);
				if (inter)
				{
					j = 0;
					while (inter[j])
						j++;
					if (j > 1)
					{
						j = 0;
						while (inter[j])
						{
							str = ft_strjoin(inter[j], " ");
							args = expantion(str, args);
							free(str);
							j++;
						}
					}
					else if (j == 1)
						args = expantion(inter[0], args);
					clear_arr_of_strs(inter);
				}
			}
			else
			{
				str = node->args[i];
				args = expantion(str, args);
			}
			i++;
		}
		clear_arr_of_strs(node->args);
		node->args = args;
	}
}

static	void	preexecute(t_ast_node *node, t_terminal *tty)
{
	if (node->args_index == 0)
	{
		parse_command(node, tty);
		detect_in_redirection(node, tty);
		detect_out_redirection(node);
	}
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
	preexecute(node, tty);
	if (execute((node->args + node->args_index), tty) == -1)
		cleanup("Error executing command", 126);
}

static	void	builtin_end(t_ast_node *node, int hold, t_terminal *tty)
{
	set_history_status(0, tty);
	if (node->parent)
		node->parent->exit = 0;
	if (hold)
		exit(1);
}

static	int	check_options(t_ast_node *node, int hold, t_terminal *tty)
{
	int	i;

	i = 1;
	if (node->args[0] == NULL)
		return (1);
	while (node->args[i])
	{
		if (node->args[i][0] == '-')
		{
			if (ft_cmpexact(node->args[0], "echo") && \
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

void	builtin_selector(t_ast_node *node, int should_exit, t_terminal *tty)
{
	if (node->args[0] == NULL)
		(void) node;
	else if (ft_cmpexact(node->args[0], "cd"))
		cd_bi(node, tty);
	else if (ft_cmpexact(node->args[0], "exit"))
		exit_bi(node, tty);
	else if (ft_cmpexact(node->args[0], "pwd"))
		pwd_bi(node);
	else if (ft_cmpexact(node->args[0], "env"))
		env_bi(node, 0, tty);
	else if (ft_cmpexact(node->args[0], "export"))
		export_bi(node, tty);
	else if (ft_cmpexact(node->args[0], "unset"))
		unset_bi(node, tty);
	else if (ft_cmpexact(node->args[0], "echo"))
		echo_bi(node);
	if (should_exit)
		exit(0);
}

static	void	builtin(t_ast_node *node, int hold, t_terminal *tty)
{
	(void) tty;
	if (check_options(node, hold, tty))
	{
		preexecute(node, tty);
		builtin_selector(node, 0, tty);
		postexecute(node);
		builtin_end(node, hold, tty);
	}
}

void	forker(t_ast_node *node, void (*f)(t_ast_node *node, int hold, \
	t_terminal *tty), t_terminal *tty)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		cleanup("Error forking process", 1);
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
	in_redirect_first(node, tty);
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
