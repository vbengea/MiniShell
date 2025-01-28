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

int	here_doc(char *delimit)
{
	char	*str;
	int		str_len;
	int		fd;

	fd = open("__tmp__", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	str = get_next_line(STDIN_FILENO);
	str_len = ft_strlen(str);
	while (ft_strncmp(str, delimit, str_len - 1) != 0)
	{
		write(fd, str, ft_strlen(str));
		free(str);
		str = get_next_line(STDIN_FILENO);
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
