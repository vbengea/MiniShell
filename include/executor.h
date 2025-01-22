/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaflore <juaflore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:32 by juaflore          #+#    #+#             */
/*   Updated: 2025/01/22 14:27:47 by juaflore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# include "../libft/libft.h"

int		execute(char *cmd, char **arvp);
void	parent(int files[2], char **arvp, char **commands, int fd[2]);
void	children(int fd[2], int files[2], char **commands, char **arvp);
void	pipex(int files[2], char **arvp, char **commands);
void	process(int argc, char **argv, char **arvp, int files[2]);

char	*environment(char *name, char **env);
char	*find_path(char *cmd, char *env);
void	cleanup(char *err, char **commands);
int		doexec(char *path, char **comm, char **arvp, int is_free);

int		argument_index(char **argv);

typedef enum node_type {
	AND,
	OR,
	PIPE,
	EXEC
}	node_type;

typedef struct s_node
{
	enum node_type	type;
	char			*value;
	char 			*stdin;
	char			*stdout;
	struct s_node	**children;
}	t_node;

#endif
