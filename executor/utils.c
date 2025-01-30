/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/25 16:49:17 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/headers.h"

void	cleanup(char *err)
{
	perror(err);
	exit(1);
}

void	waiter(t_node_type type)
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

int    is_builtin(t_ast_node *node)
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

int    is_pipe_state(t_ast_node *node)
{
	if (node->parent_type == NODE_PIPE)
		return (1);
	return (0);
}

int	here_doc(char *delimit, int stdin)
{
	char	*str;
	int		str_len;
	int		fd;

	fd = open("__tmp__", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	str = get_next_line(stdin);
	str_len = ft_strlen(str);
	while (ft_strncmp(str, delimit, str_len - 1) != 0)
	{
		write(fd, str, ft_strlen(str));
		free(str);
		str = get_next_line(stdin);
		str_len = ft_strlen(str);
	}
	free(str);
	close(fd);
	return (open("__tmp__", O_RDONLY));
}

void	populate_node(t_ast_node *node, int side)
{
	if (!node->left)
	{
		node->left = malloc(sizeof(t_ast_node));
		node->left->left = NULL;
		node->left->right = NULL;
	}
	if (!node->right)
	{
		node->right = malloc(sizeof(t_ast_node));
		node->right->left = NULL;
		node->right->right = NULL;
	}
	node->left->parent = node;
	node->right->parent = node;
	node->right->parent_type = node->type;
	node->left->parent_type = node->type;
	node->right->side = 1;
	node->left->side = 0;
	node->side = side;
}

static	char **	args_helper(char *arg1, char *arg2)
{
	char **arr = malloc(sizeof(char *) * 3);
	arr[0] = ft_strdup(arg1);
	arr[1] = ft_strdup(arg2);
	arr[2] = NULL;
	return (arr);
}

t_ast_node	*build_redirect_ast(void)
{
	// INFILE
	t_ast_node	*root = create_ast_node(NODE_PIPE, NULL);
	root->left = create_ast_node(NODE_REDIRECT, NULL);
	root->left->redirect_type = REDIRECT_IN;
	root->left->file = ft_strdup("t1");
	root->left->left = create_ast_node(NODE_CMND, args_helper("cat", "-e"));
	root->right = create_ast_node(NODE_CMND,  args_helper("cat", "-e"));

	// // HERE_DOC
	// t_ast_node	*root = create_ast_node(NODE_PIPE, NULL);
	// root->left = create_ast_node(NODE_REDIRECT, NULL);
	// root->left->redirect_type = REDIRECT_HEREDOC;
	// root->left->file = ft_strdup("EOF");
	// root->left->left = create_ast_node(NODE_CMND, args_helper("cat", "-e"));
	// root->right = create_ast_node(NODE_CMND,  args_helper("cat", "-e"));

	// OUTFILE
	// t_ast_node	*root = create_ast_node(NODE_PIPE, NULL);
	// root->left = create_ast_node(NODE_CMND, args_helper("ls", "-l"));
	// root->right = create_ast_node(NODE_REDIRECT, NULL);
	// root->right->redirect_type = REDIRECT_OUT;
	// root->right->file = ft_strdup("t1");
	// root->right->left = create_ast_node(NODE_CMND,  args_helper("cat", "-e"));
	return (root);
}
