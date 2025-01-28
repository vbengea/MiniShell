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

static	void	waiter(t_node_type type)
{
	int		status;

	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			if (access("__tmp__", F_OK) == 0)
				unlink("__tmp__");
			if (status != 0 && type == NODE_AND)
				exit(0);
			else if (status == 0 && type == NODE_OR)
				exit(0);
			break ;
		}
	}
}

static  void    cenv(void)
{

}

static  void    navigate(t_ast_node *node, char **env, int hold)
{
	(void) hold;
	selector(node->left, env);
	selector(node->right, env);
}

static  void    executor(t_ast_node *node, char **env, int hold)
{
	(void) hold;
	if (execute(node->args, env) == -1)
		cleanup("Error executing command..");
}

static  void    builtin(t_ast_node *node, char **env, int hold)
{
	if (ft_strncmp(node->args[0], "cd", 2) == 0)
	{
		cd(node->args[1], env);
		if (hold)
			exit(0);
	}
}

static  void    forker(t_ast_node *node, char **env, void (*f)(t_ast_node *node, char **env, int hold))
{
	int	pid;

	pid = fork();
	if (pid == -1)
		cleanup("Error forking process");
	if (pid == 0)
		f(node, env, 1);
	else
	{
		waiter(node->parent_type);
	}
}

static  int    is_builtin(t_ast_node *node)
{
	char	*b[8] = { "cd", "echo", "env", "exit", "export", "pwd", "unset", NULL };
	int		i = 0;
	while (b[i])
	{
		if (ft_strncmp(node->args[0], b[i], ft_strlen(b[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

static  int    is_pipe_state(t_ast_node *node)
{
	if (node->parent_type == NODE_PIPE)
		return (1);
	return (0);
}

void	selector(t_ast_node *node, char **env)
{
    if (node->type == NODE_CMND)
    {
        if (is_builtin(node))
        {
            if (is_pipe_state(node))
                forker(node, env, builtin);
            else
                builtin(node, env, 0);
        }
        else
            forker(node, env, executor);
    }
    else if (node->type == NODE_AND)
    {
		navigate(node, env, 0);
    }
    else if (node->type == NODE_PIPE)
    {
		forker(node, env, navigate);
    }
    else if (node->type == NODE_GROUP)
    {
		(void) cenv;
        forker(node, env, navigate);
    }
}