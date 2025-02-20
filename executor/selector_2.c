/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflores <jflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:47:46 by jflores           #+#    #+#             */
/*   Updated: 2025/02/20 18:26:10 by jflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

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
		cleanup(NULL, 0, node, tty);
	}
}

void	executor(t_ast_node *node, int hold, t_terminal *tty)
{
	(void) hold;
	preexecute(node, tty);
	if (execute(node, node->args, tty) == -1)
		cleanup("Error executing command", 126, node, tty);
}

void	builtin_end(t_ast_node *node, int hold, t_terminal *tty)
{
	set_history_status(0, tty);
	if (node->parent)
		node->parent->exit = 0;
	if (hold)
		exit(1);
}

int	check_options(t_ast_node *node, int hold, t_terminal *tty)
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
	else if (ft_cmpexact(node->args[node->args_index], "cd"))
		cd_bi(node, tty);
	else if (ft_cmpexact(node->args[node->args_index], "exit"))
		exit_bi(node, tty);
	else if (ft_cmpexact(node->args[node->args_index], "pwd"))
		pwd_bi(node);
	else if (ft_cmpexact(node->args[node->args_index], "env"))
		env_bi(node, 0, tty);
	else if (ft_cmpexact(node->args[node->args_index], "export"))
		export_bi(node, tty);
	else if (ft_cmpexact(node->args[node->args_index], "unset"))
		unset_bi(node, tty);
	else if (ft_cmpexact(node->args[node->args_index], "echo"))
		echo_bi(node);
	if (should_exit)
	{
		multiple_output_redirections(node, tty);
		cleanup(NULL, 0, node, tty);
	}
}
