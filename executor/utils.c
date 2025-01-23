/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:48:23 by jflores           #+#    #+#             */
/*   Updated: 2025/01/22 12:39:21 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

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

static	void	ennode(t_node *s, enum node_type type, int n)
{
	int		i;

	i = 0;
	s->type = type;
	s->children = malloc(sizeof(t_node *) * (n + 1));
	if (s->children)
	{
		while (i < n)
		{
			s->children[i] = malloc(sizeof(t_node));
			if (!s->children[i])
				exit(1);
			i++;
		}
		s->children[n] = NULL;
	}
	else
		exit(1);
}